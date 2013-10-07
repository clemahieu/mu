#include <mu/llvmc/analyzer.hpp>

#include <mu/core/error_string.hpp>
#include <mu/llvmc/ast.hpp>
#include <mu/llvmc/skeleton.hpp>
#include <mu/llvmc/ast_t.hpp>
#include <mu/llvmc/skeleton_t.hpp>

#include <boost/lexical_cast.hpp>

#include <gc_cpp.h>

#include <typeinfo>

#include <inttypes.h>

mu::llvmc::branch_analyzer::branch_analyzer (mu::llvmc::skeleton::branch * global_a, mu::core::error * & result_a) :
global (global_a),
most_specific (global_a),
result (result_a)
{
}

mu::llvmc::skeleton::branch * mu::llvmc::branch_analyzer::add_branch (mu::llvmc::skeleton::branch * branch_a, mu::core::region const & region_a)
{
	auto most_specific_l (most_specific->most_specific (branch_a));
	if (most_specific_l != nullptr)
	{
		most_specific = most_specific_l;
	}
	else
	{
		result = new (GC) mu::core::error_string (U"Branches are disjoint", mu::core::error_type::branch_analyzer_disjoint, region_a);
	}
    return most_specific_l;
}

void mu::llvmc::branch_analyzer::new_set ()
{
	auto existing_leaf (leaves.find (most_specific));
	if (existing_leaf == leaves.end ())
	{
		auto existing_ancestor (ancestors.find (most_specific));
		if (existing_ancestor == ancestors.end ())
		{
			mu::set <mu::llvmc::skeleton::branch *> ancestors_l;
			auto branch_l (most_specific->parent);
			while (branch_l != nullptr)
			{
				ancestors_l.insert (branch_l);
				branch_l = branch_l->parent;
			}
			mu::vector <mu::llvmc::skeleton::branch *> same (std::max (ancestors_l.size (), leaves.size ()));
			auto final (std::set_intersection (ancestors_l.begin (), ancestors_l.end (), leaves.begin (), leaves.end (), same.begin ()));
			if (final == same.begin ())
			{
				ancestors.insert (ancestors_l.begin (), ancestors_l.end ());
				leaves.insert (most_specific);
				most_specific = global;
			}
			else
			{
				result = new (GC) mu::core::error_string (U"Result branch is not unique", mu::core::error_type::branch_analyzer_intersection_exists);
			}
		}
		else
		{
			result = new (GC) mu::core::error_string (U"Result branch is not unique", mu::core::error_type::branch_analyzer_ancestor_exists);
		}
	}
	else
	{
		result = new (GC) mu::core::error_string (U"Result branch is not unique", mu::core::error_type::branch_analyzer_leaves_exist);
	}
}

class global_naming : public mu::llvmc::skeleton::visitor
{
public:
	global_naming (mu::llvmc::module_processor & module_a, mu::core::error * & error_a, mu::string const & name_a) :
	module (module_a),
	error (error_a),
	name (name_a)
	{
	}
	void node (mu::llvmc::skeleton::node * node_a) override
	{
		// Non-globals can be named anything
	}
	void global_value (mu::llvmc::skeleton::global_value * node_a) override
	{
		auto existing (module.named_globals.find (node_a));
		if (existing == module.named_globals.end ())
		{
			auto removed (module.unnamed_globals.erase (node_a));
			assert (removed == 1);
			module.named_globals.insert (node_a);
			module.module_m->globals.push_back (node_a);
			assert (node_a->name.empty ());
			node_a->name = name;
		}
		else
		{
			error = new mu::core::error_string (U"Global already has a name", mu::core::error_type::global_already_named);
		}
	}
    mu::llvmc::module_processor & module;
	mu::core::error * & error;
	mu::string const & name;
};

class module_analyzer : public mu::llvmc::skeleton::visitor
{
public:
    module_analyzer (mu::llvmc::module_processor & module_a, mu::core::error * & error_a) :
    module (module_a),
	error (error_a)
    {
    }
	void node (mu::llvmc::skeleton::node * node_a) override
	{
		error = new (GC) mu::core::error_string (U"Unexpected node type in module", mu::core::error_type::unexpected_node_type);
	}
    void named (mu::llvmc::skeleton::named * node_a) override
    {
        node_a->value_m->visit (this);
		if (error == nullptr)
		{
			global_naming naming (module, error, node_a->name);
			node_a->value_m->visit (&naming);
		}
    }
	void global_value (mu::llvmc::skeleton::global_value * node_a) override
	{
		written_but_not_generated (node_a);
	}
    void constant (mu::llvmc::skeleton::constant * node_a) override
    {
		written_but_not_generated (node_a);
    }
    void type (mu::llvmc::skeleton::type * node_a) override
    {
		written_but_not_generated (node_a);
    }
    void template_c (mu::llvmc::skeleton::template_c * node_a) override
    {
		written_but_not_generated (node_a);
    }
	void written_but_not_generated (mu::llvmc::skeleton::node * node_a)
	{
        // Nodes that can be written at module level but are not generated at the module level
	}
    mu::llvmc::module_processor & module;
	mu::core::error * & error;
};
				
mu::llvmc::global_processor::global_processor (mu::core::error * & error_a) :
current_context (this),
error (error_a)
{
}
				
void mu::llvmc::global_processor::node (mu::llvmc::ast::node * node_a)
{
	error = new (GC) mu::core::error_string (U"Expecting a module", mu::core::error_type::expecting_a_module, node_a->region);
}

mu::llvmc::module_processor::module_processor (mu::llvmc::global_processor & global_a) :
global_m (global_a),
module_m (new (GC) mu::llvmc::skeleton::module),
parent (global_a.current_context)
{
	global_a.current_context = this;
}

mu::llvmc::module_processor::~module_processor ()
{
	global_m.current_context = parent;
}

void mu::llvmc::global_processor::module (mu::llvmc::ast::module * node_a)
{
	mu::llvmc::module_processor processor (*this);
	auto module_s (processor.module_m);
	module_analyzer analyzer (processor, error);
	for (auto i (node_a->globals.begin ()), j (node_a->globals.end ()); i != j && error == nullptr; ++i)
	{
		if (!(*i)->assigned)
		{
			process_node (*i);
		}
		if (error == nullptr)
		{
			assert ((*i)->assigned);
			auto & values ((*i)->generated);
			for (auto k (values.begin ()), l (values.end ()); k != l && error == nullptr; ++k)
			{
				auto value (*k);
				value->visit (&analyzer);
			}
		}
	}
    if (error == nullptr)
    {
        for (auto i: node_a->names)
        {
            assert (i.second->assigned);
            assert (module_s->names.find (i.first) == module_s->names.end ());
            assert (i.second->generated.size () == 1);
            module_s->names [i.first] = i.second->generated [0];
        }
		node_a->assigned = true;
		node_a->generated.push_back (module_s);
    }
}

class module_checker : public mu::llvmc::skeleton::visitor
{
public:
	module_checker (mu::core::error * & error_a, mu::core::region & region_a) :
	error (error_a),
	region (region_a)
	{
	}
	void node (mu::llvmc::skeleton::node * node_a)
	{
		error = new (GC) mu::core::error_string (U"Expecting a module", mu::core::error_type::expecting_a_module, region);
	}
	void module (mu::llvmc::skeleton::module * node_a)
	{
		//Expecting a module;
	}
	mu::core::error * & error;
	mu::core::region & region;
};

mu::llvmc::module_result mu::llvmc::analyzer::analyze (mu::llvmc::ast::node * module_a)
{
	mu::llvmc::module_result result ({nullptr, nullptr});
	mu::llvmc::global_processor analyzer_l (result.error);
	module_a->visit (&analyzer_l);
	if (result.error == nullptr)
	{
		module_checker checker (result.error, module_a->region);
		assert (module_a->generated.size () == 1);
		if (result.error == nullptr)
		{
			result.module = mu::cast <mu::llvmc::skeleton::module> (module_a->generated [0]);
		}
	}
	return result;
}

void mu::llvmc::function_processor::process_parameters ()
{
	for (auto k (node_m->parameters.begin ()), l (node_m->parameters.end ()); k != l && error == nullptr; ++k)
	{
		auto parameter (mu::cast <mu::llvmc::ast::parameter> (*k));
        auto node (parameter->type);
		auto type_l (process_type (node));
		if (type_l != nullptr)
		{
			auto parameter_s (new (GC) mu::llvmc::skeleton::parameter (parameter->region, function_m->entry, type_l, parameter->name));
			parameter->generated.push_back (parameter_s);
			parameter->assigned = true;
			function_m->parameters.push_back (parameter_s);
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_type_in_parameters, node->region);
		}
	}
}

void mu::llvmc::function_processor::node (mu::llvmc::ast::node * node_a)
{
	node_a->visit (&module_m);
}

void mu::llvmc::function_processor::value (mu::llvmc::ast::value * value_node)
{
	auto value (dynamic_cast <mu::llvmc::skeleton::value *> (value_node->node_m));
	if (value != nullptr)
	{
		assert (value->branch == nullptr);
		value->branch = module_m.module_m->global;
	}
	value_node->generated.push_back (value_node->node_m);
	value_node->assigned = true;
}

void mu::llvmc::function_processor::integer_type (mu::llvmc::ast::integer_type * type_a)
{
	try
	{
		std::string data_l (type_a->bits.begin (), type_a->bits.end ());
		unsigned int bits (boost::lexical_cast <unsigned int> (data_l));
		if (bits <= 1024)
		{
			type_a->generated.push_back (new (GC) mu::llvmc::skeleton::integer_type (bits));
			type_a->assigned = true;
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Bit width too wide", mu::core::error_type::bit_width_too_wide, type_a->region);
		}
	}
	catch (boost::bad_lexical_cast)
	{
		error = new (GC) mu::core::error_string (U"Unable to convert number to unsigned integer", mu::core::error_type::unable_to_convert_number_to_unsigned_integer, type_a->region);
	}
}

class naming_visitor : public mu::llvmc::skeleton::visitor
{
public:
    naming_visitor (mu::llvmc::module_processor & module_a, mu::llvmc::ast::element * element_a, mu::core::error * & error_a) :
	module (module_a),
    element (element_a),
    error (error_a)
    {
    }
    void node (mu::llvmc::skeleton::node * node_a)
    {
        element->generated.push_back (node_a);
    }
    void value (mu::llvmc::skeleton::value * node_a)
    {
        element->generated.push_back (new (GC) mu::llvmc::skeleton::named (element->region, node_a, element->name));
    }
	void global_value (mu::llvmc::skeleton::global_value * node_a)
	{
		global_naming naming (module, error, element->name);
		node_a->visit (&naming);
		element->generated.push_back (node_a);
	}
	mu::llvmc::module_processor & module;
    mu::llvmc::ast::element * element;
    mu::core::error * & error;
};

void mu::llvmc::module_processor::element (mu::llvmc::ast::element * element_a)
{
	global_m.process_node (element_a->node_m);
	if (global_m.error == nullptr)
	{
		assert (element_a->node_m->assigned);
		auto & existing (element_a->node_m->generated);
		if (existing.size () > element_a->index)
		{
			auto node (existing [element_a->index]);
            naming_visitor naming (*this, element_a, global_m.error);
            node->visit (&naming);
			if (global_m.error == nullptr)
			{
				element_a->assigned = true;
			}
		}
		else
		{
			global_m.error = new (GC) mu::core::error_string (U"No value at index", mu::core::error_type::no_value_at_index, element_a->region);
		}
	}
}

void mu::llvmc::function_processor::unit (mu::llvmc::ast::unit * node_a)
{
	node_a->generated.push_back (&module_m.module_m->the_unit_value);
	node_a->assigned = true;
}

void mu::llvmc::function_processor::constant_int (mu::llvmc::ast::constant_int * constant_a)
{
	try
	{
		std::string data_l (constant_a->bits.begin (), constant_a->bits.end ());
		unsigned int bits (boost::lexical_cast <unsigned int> (data_l));
		if (bits <= 1024)
		{
			auto number (dynamic_cast<mu::llvmc::ast::number *> (constant_a->number));
			if (number != nullptr)
			{
				auto number_l (process_number (number));
				if (number_l != nullptr)
				{
					constant_a->generated.push_back (new (GC) mu::llvmc::skeleton::constant_integer (constant_a->region, module_m.module_m->global, bits, number_l->value));
					constant_a->assigned = true;
				}
			}
			else
			{
				error = new (GC) mu::core::error_string (U"Expecting a number", mu::core::error_type::expecting_a_number, constant_a->number->region);
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Bit width too wide", mu::core::error_type::bit_width_too_wide, constant_a->region);
		}
	}
	catch (boost::bad_lexical_cast)
	{
		error = new (GC) mu::core::error_string (U"Unable to convert number to unsigned integer", mu::core::error_type::unable_to_convert_number_to_unsigned_integer, constant_a->region);
	}
}

void mu::llvmc::function_processor::pointer_type (mu::llvmc::ast::pointer_type * type_a)
{
	auto pointed_type (process_type (type_a->pointed_type));
	if (pointed_type != nullptr)
	{
		type_a->generated.push_back (new (GC) mu::llvmc::skeleton::pointer_type (pointed_type));
		type_a->assigned = true;
	}
}

void mu::llvmc::function_processor::asm_c (mu::llvmc::ast::asm_c * asm_l)
{
	auto type (process_type (asm_l->type));
	if (type != nullptr)
	{
		asm_l->generated.push_back (new (GC) mu::llvmc::skeleton::asm_c (type, asm_l->text, asm_l->constraints));
		asm_l->assigned = true;
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_a_type, asm_l->type->region);
	}
}

void mu::llvmc::function_processor::number (mu::llvmc::ast::number * node_a)
{
	error = new (GC) mu::core::error_string (U"Numbers must be parsed by a keyword", mu::core::error_type::numbers_parsed_by_keyword);
}

void mu::llvmc::function_processor::array_type (mu::llvmc::ast::array_type * type_a)
{
	auto element (process_type (type_a->element_type));
	if (element != nullptr)
	{
		auto number (dynamic_cast <mu::llvmc::ast::number *> (type_a->size));
		if (number != nullptr)
		{
			auto number_l (process_number (number));
			if (number_l != nullptr)
			{
				type_a->generated.push_back (new (GC) mu::llvmc::skeleton::array_type (element, number_l->value));
				type_a->assigned = true;
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Expecting number", mu::core::error_type::expecting_a_number, type_a->size->region);
		}
	}
}

void mu::llvmc::function_processor::constant_array (mu::llvmc::ast::constant_array * array_a)
{
	auto type (process_type (array_a->type));
	if (type != nullptr)
	{
		mu::vector <mu::llvmc::skeleton::constant *> initializer;
		for (auto i (array_a->initializer.begin ()), j (array_a->initializer.end ()); i != j && error == nullptr; ++i)
		{
			module_m.global_m.process_node (*i);
			auto & values ((*i)->generated);
			for (auto k (values.begin ()), l (values.end ()); k != l && error == nullptr; ++k)
			{
				auto constant (dynamic_cast <mu::llvmc::skeleton::constant *> (*k));
				if (constant != nullptr)
				{
					if (*type == *constant->type ())
					{
						initializer.push_back (constant);
					}
					else
					{
						error = new (GC) mu::core::error_string (U"Initializer type doesn't match array element type", mu::core::error_type::initializer_type_doesnt_match, (*i)->region);
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Initializer must be a constant", mu::core::error_type::initializer_must_be_constant, (*i)->region);
				}
			}
		}
		auto array_type (new (GC) mu::llvmc::skeleton::array_type (type, initializer.size ()));
		array_a->generated.push_back (new (GC) mu::llvmc::skeleton::constant_array (array_a->region, module_m.module_m->global, array_type, initializer));
		array_a->assigned = true;
	}
}

void mu::llvmc::function_processor::global_variable (mu::llvmc::ast::global_variable * global_variable)
{
	module_m.global_m.process_node (global_variable->initializer);
	auto & values (global_variable->initializer->generated);
	if (values.size () == 1)
	{
		auto constant (dynamic_cast <mu::llvmc::skeleton::constant *> (values [0]));
		if (constant != nullptr)
		{
			global_variable->assigned = true;
			auto & targets (global_variable->generated);
			assert (targets.empty ());
			auto skeleton (new (GC) mu::llvmc::skeleton::global_variable (global_variable->region, module_m.module_m->global, constant));
            assert (module_m.unnamed_globals.find (skeleton) == module_m.unnamed_globals.end ());
            module_m.unnamed_globals.insert (skeleton);
			targets.push_back (skeleton);
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Global variables must have constant initializers", mu::core::error_type::global_constant_initializer, global_variable->initializer->region);
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Global variables expect one initializer", mu::core::error_type::global_one_initializer, global_variable->initializer->region);
	}
}

void mu::llvmc::function_processor::constant_pointer_null (mu::llvmc::ast::constant_pointer_null * constant_pointer_null)
{
	auto type (process_type (constant_pointer_null->type));
	if (type != nullptr)
	{
		auto pointer (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (type));
		if (pointer != nullptr)
		{
			constant_pointer_null->assigned = true;
			auto & values (constant_pointer_null->generated);
			auto skeleton (new (GC) mu::llvmc::skeleton::constant_pointer_null (constant_pointer_null->region, module_m.module_m->global, type));
			values.push_back (skeleton);
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Type is not a pointer", mu::core::error_type::expecting_a_pointer_type, constant_pointer_null->type->region);
		}
	}
}

void mu::llvmc::function_processor::unit_type (mu::llvmc::ast::unit_type * unit_type)
{
	auto & values (unit_type->generated);
	unit_type->assigned = true;
	values.push_back (&module_m.module_m->the_unit_type);
}

void mu::llvmc::function_processor::join (mu::llvmc::ast::join * node_a)
{
	mu::llvmc::branch_analyzer analyzer_l (module_m.module_m->global, error);
	auto join (new (GC) mu::llvmc::skeleton::join_value);
	for (auto & i: node_a->branches)
	{
		auto & target (join->add_branch ());
		for (auto j: i.arguments)
		{
			module_m.global_m.process_node (j);
			if (error == nullptr)
			{
				auto & values (j->generated);
				for (auto k: values)
				{
					auto value (dynamic_cast <mu::llvmc::skeleton::value *> (k));
					if (value != nullptr)
					{
						target.arguments.push_back (value);
						analyzer_l.add_branch (value->branch, value->region);
					}
					else
					{
						error = new (GC) mu::core::error_string (U"Join arguments must be values", mu::core::error_type::join_arguments_must_be_values, j->region);
					}
				}
			}
		}
		for (auto j: i.predicates)
		{
			module_m.global_m.process_node (j);
			if (error == nullptr)
			{
				auto & values (j->generated);
				for (auto k: values)
				{
					auto value (dynamic_cast <mu::llvmc::skeleton::value *> (k));
					if (value != nullptr)
					{
						target.predicates.push_back (value);
						analyzer_l.add_branch (value->branch, value->region);
					}
					else
					{
						error = new (GC) mu::core::error_string (U"Join arguments must be values", mu::core::error_type::join_arguments_must_be_values, j->region);
					}
				}
			}
		}
		analyzer_l.new_set ();
	}
	if (error == nullptr)
	{
		if (join->branches.size () > 1)
		{
			auto size (join->branches [0].arguments.size ());
			if (size > 0)
			{
				mu::vector <mu::llvmc::skeleton::type *> types;
				for (auto i: join->branches [0].arguments)
				{
					types.push_back (i->type ());
				}
				for (auto & i: join->branches)
				{
					if (i.arguments.size () == size)
					{
						size_t index (0);
						for (auto j: i.arguments)
						{
							if (*j->type() != *types [index])
							{
								error = new (GC) mu::core::error_string (U"Join argument types must match for each branch", mu::core::error_type::joining_types_are_different, node_a->region);
							}
							++index;
						}
					}
					else
					{
						error = new (GC) mu::core::error_string (U"Join branches must have same cardinality", mu::core::error_type::join_branches_same_cardinality, node_a->region);
					}
				}
				if (error == nullptr)
				{
					assert (!analyzer_l.leaves.empty ());
					auto least_specific_branch (*analyzer_l.leaves.begin ());
					for (auto i: analyzer_l.leaves)
					{
						least_specific_branch = least_specific_branch->least_specific (i);
					}
					assert (least_specific_branch != module_m.module_m->global);
					auto & elements (join->elements);
					auto & generated (node_a->generated);
					node_a->assigned = true;
					for (auto i: types)
					{
						auto element (new (GC) mu::llvmc::skeleton::join_element (node_a->region, least_specific_branch->parent, join, i));
						generated.push_back (element);
						elements.push_back (element);
					}
				}
			}
			else
			{
				error = new (GC) mu::core::error_string (U"Joining branches must contain at least one value", mu::core::error_type::must_be_joining_at_least_two_values, node_a->region);
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Must be joining at least two branches", mu::core::error_type::must_be_joining_at_least_two_branches, node_a->region);
		}
	}
}

void mu::llvmc::module_processor::node (mu::llvmc::ast::node * node_a)
{
	node_a->visit (&global_m);
}

void mu::llvmc::module_processor::function (mu::llvmc::ast::function * function_node)
{
	assert (function_node->branch_ends.size () == function_node->predicate_offsets.size ());
	
	mu::llvmc::function_processor nodes (*this, global_m.error, module_m->global, function_node);
	nodes.process ();
}

void mu::llvmc::function_processor::process ()
{
    process_parameters ();
	process_results ();
	if (error == nullptr)
	{
		node_m->generated.push_back (function_m);
		node_m->assigned = true;
        assert (module_m.unnamed_globals.find (function_m) == module_m.unnamed_globals.end ());
        module_m.unnamed_globals.insert (function_m);
	}
}

void mu::llvmc::module_processor::entry (mu::llvmc::ast::entry * node_a)
{
	global_m.process_node (node_a->function);
    if (global_m.error == nullptr)
    {
        assert (node_a->function->assigned);
        if (node_a->function->generated.size () == 1)
        {
            if (module_m->entry == nullptr)
            {
                auto function_l (dynamic_cast <mu::llvmc::skeleton::function *> (node_a->function->generated [0]));
                if (function_l != nullptr)
                {
                    if (function_l->parameters.size () == 0)
                    {
                        if (function_l->branch_ends.size () == 1)
                        {
                            assert (function_l->predicate_offsets.size () == 1);
                            if (function_l->predicate_offsets [0] == 0)
                            {
								module_m->entry = function_l;
                                node_a->generated.push_back (function_l);
                                node_a->assigned = true;
                            }
                            else
                            {
                                global_m.error = new (GC) mu::core::error_string (U"Entry point function cannot return values", mu::core::error_type::entry_point_cannot_return_values);
                            }
                        }
                        else
                        {
                            global_m.error = new (GC) mu::core::error_string (U"Entry point function must have one return branch", mu::core::error_type::entry_point_must_have_one_return_branch);
                        }
                    }
                    else
                    {
                        global_m.error = new (GC) mu::core::error_string (U"Entry point function must take no arguments", mu::core::error_type::entry_point_must_have_no_arguments);
                    }
                }
                else
                {
                    global_m.error = new (GC) mu::core::error_string (U"Entry point must be a function", mu::core::error_type::entry_point_must_be_a_function);
                }
            }
            else
            {
                global_m.error = new (GC) mu::core::error_string (U"Entry point has already been defined", mu::core::error_type::only_one_entry_point);
            }
        }
        else
        {
            global_m.error = new (GC) mu::core::error_string (U"Only one function can be defined as the entry point", mu::core::error_type::only_one_entry_point);
        }
    }
}

void mu::llvmc::function_processor::loop (mu::llvmc::ast::loop * loop_a)
{
	auto loop_s (new (GC) mu::llvmc::skeleton::loop (&module_m.module_m->the_unit_type));
	mu::llvmc::skeleton::branch * loop_branch (module_m.module_m->global);
	size_t predicate_offset (~0);
	process_call_values (loop_a->arguments, loop_a->argument_predicate_offset, loop_s->arguments, loop_branch, predicate_offset);
	loop_s->argument_predicate_offset = predicate_offset;
	if (error == nullptr)
	{
		if (loop_s->arguments.size () == loop_a->parameters.size ())
		{
			auto loop_entry_branch (new (GC) mu::llvmc::skeleton::branch (loop_branch));
			loop_s->loop_entry_branch = loop_entry_branch;
			auto i (loop_a->parameters.begin ());
			auto j (loop_a->parameters.end ());
			auto k (loop_s->arguments.begin ());
			for (; i != j; ++i, ++k)
			{
				auto parameter (mu::cast <mu::llvmc::ast::loop_parameter> (*i));
				auto argument (dynamic_cast<mu::llvmc::skeleton::value *> (*k));
				if (argument != nullptr)
				{
					auto new_parameter (new (GC) mu::llvmc::skeleton::loop_parameter (loop_a->region, loop_entry_branch, static_cast<mu::llvmc::skeleton::value *> (*k)->type (), parameter->name));
					loop_s->parameters.push_back (new_parameter);
					parameter->assigned = true;
					parameter->generated.push_back (new_parameter);
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Loop argument must be a value", mu::core::error_type::loop_argument_must_be_value);
				}
			}
			auto branch (new (GC) mu::llvmc::skeleton::branch (loop_branch));
			auto empty (true);
			auto feedback_branch (true);
			mu::llvmc::branch_analyzer branches (module_m.module_m->global, error);
			loop_a->for_each_results (
									  [&]
									  (mu::llvmc::ast::node * expression_a, size_t index_a)
									  {
										  module_m.global_m.process_node (expression_a);
										  if (error == nullptr)
										  {
											  for (auto i : expression_a->generated)
											  {
												  auto value (dynamic_cast<mu::llvmc::skeleton::value *> (i));
												  if (value != nullptr)
												  {
													  branches.add_branch (value->branch, expression_a->region);
													  loop_s->results.push_back (value);
													  auto element (new (GC) mu::llvmc::skeleton::loop_element (expression_a->region, branch, loop_s, value->type ()));
													  loop_s->elements.push_back (element);
												  }
												  else
												  {
													  error = new (GC) mu::core::error_string (U"Loop result must be a value", mu::core::error_type::loop_result_must_be_value);
												  }
											  }
										  }
										  empty = false;
									  },
									  [&]
									  (mu::llvmc::ast::node * expression_a, size_t)
									  {
										  module_m.global_m.process_node (expression_a);
										  if (error == nullptr)
										  {
											  for (auto i : expression_a->generated)
											  {
												  auto value (dynamic_cast<mu::llvmc::skeleton::value *> (i));
												  if (value != nullptr)
												  {
													  branches.add_branch (value->branch, expression_a->region);
													  loop_s->results.push_back (value);
												  }
												  else
												  {
													  error = new (GC) mu::core::error_string (U"Loop result must be a value", mu::core::error_type::loop_result_must_be_value);
												  }
											  }
										  }
									  },
									  [&]
									  (mu::llvmc::ast::node * node_a, size_t index_a)
									  {
										  loop_s->predicate_offsets.push_back (loop_s->results.size ());
										  if (empty)
										  {
											  auto element (new (GC) mu::llvmc::skeleton::loop_element (node_a->region, branch, loop_s, &module_m.module_m->the_unit_type));
											  loop_s->elements.push_back (element);
										  }
									  },
									  [&]
									  (mu::llvmc::ast::node * node_a, size_t)
									  {
										  branches.new_set ();
										  loop_s->branch_ends.push_back (loop_s->results.size ());
										  branch = new (GC) mu::llvmc::skeleton::branch (loop_branch);
										  feedback_branch = false;
										  empty = true;
									  },
									  [&]
									  ()
									  {
										  return error == nullptr;
									  }
									  );
			assert (error != nullptr || loop_s->predicate_offsets.size () == loop_s->branch_ends.size ());
			if (error == nullptr)
			{
				loop_a->assigned = true;
				switch (loop_s->elements.size ())
				{
					case 0:
					{
						loop_a->generated.push_back (new (GC) mu::llvmc::skeleton::loop_element (loop_a->region, branch, loop_s, &module_m.module_m->the_unit_type));
						break;
					}
					case 1:
					{
						loop_a->generated.push_back (loop_s->elements [0]);
						break;
					}
					default:
					{
						auto & target (loop_a->generated);
						target.insert (target.end (), loop_s->elements.begin (), loop_s->elements.end ());
					}
				}
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Number of arguments does not match number of parameters", mu::core::error_type::mismatch_number_of_arguments_number_of_parameters);
		}
	}
}

void mu::llvmc::function_processor::expression (mu::llvmc::ast::expression * expression_a)
{
	auto existing (module_m.current_expression_generation.find (expression_a));
	if (existing == module_m.current_expression_generation.end ())
	{
		module_m.current_expression_generation.insert (expression_a);
		if (!expression_a->arguments.empty ())
		{
			module_m.global_m.process_node (expression_a->arguments [0]);
			if (error == nullptr)
			{
				mu::llvmc::skeleton::node * target;
				auto & generated = expression_a->arguments [0]->generated;
				if (!generated.empty ())
				{
					target = generated [0];
                    assert (target != nullptr);
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Expecting target", mu::core::error_type::expecting_a_target, expression_a->arguments [0]->region);
				}
				if (error == nullptr)
				{
					auto value (dynamic_cast <mu::llvmc::skeleton::value *> (target));
					if (value != nullptr)
					{
						process_value_call (expression_a);
					}
					else
					{
						auto marker (dynamic_cast <mu::llvmc::skeleton::marker *> (target));
						if (marker != nullptr)
						{
							process_marker (expression_a);
						}
						else
						{
							auto asm_l (dynamic_cast <mu::llvmc::skeleton::asm_c *> (target));
							if (asm_l != nullptr)
							{
								process_asm (expression_a);
							}
							else
							{
								auto identity (dynamic_cast <mu::llvmc::skeleton::identity *> (target));
								if (identity != nullptr)
								{
									process_identity (expression_a);
								}
								else
								{
									auto template_l (dynamic_cast <mu::llvmc::skeleton::template_c *> (target));
									if (template_l != nullptr)
									{
										process_template (expression_a);
									}
									else
									{
										error = new (GC) mu::core::error_string (U"Expecting first argument to be call target", mu::core::error_type::expecting_first_argument_to_be_call_target, expression_a->arguments [0]->region);
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Expecting a call target", mu::core::error_type::expecting_a_call_target, expression_a->region);
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Cycle in expressions", mu::core::error_type::cycle_in_expressions, expression_a->region);
	}
	module_m.current_expression_generation.erase (expression_a);
	assert (module_m.current_expression_generation.find (expression_a) == module_m.current_expression_generation.end ());
}

void mu::llvmc::function_processor::struct_type (mu::llvmc::ast::struct_type * node_a)
{
	auto struct_l (new (GC) mu::llvmc::skeleton::struct_type);
	for (auto i: node_a->elements)
	{
		auto type (process_type (i));
		if (type != nullptr)
		{
			struct_l->elements.push_back (type);
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Struct type definition must list other types", mu::core::error_type::struct_must_contain_types, i->region);
		}
	}
	if (error == nullptr)
	{
		node_a->assigned = true;
		node_a->generated.push_back (struct_l);
	}
}

void mu::llvmc::function_processor::undefined (mu::llvmc::ast::undefined * node_a)
{
	auto type (process_type (node_a->type));
	if (type != nullptr)
	{
		auto undefined_l (new (GC) mu::llvmc::skeleton::undefined (node_a->region, module_m.module_m->global, type));
		node_a->assigned = true;
		node_a->generated.push_back (undefined_l);
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_a_type, node_a->region);
	}
}

void mu::llvmc::function_processor::template_c (mu::llvmc::ast::template_c * node_a)
{
	auto node (new (GC) mu::llvmc::skeleton::template_c (node_a->base));
	node->body = node_a->body;
	node_a->assigned = true;
	node_a->generated.push_back (node);
}

namespace mu
{
    namespace llvmc
    {
		class process_template : public mu::llvmc::ast::visitor
		{
		public:
			process_template (mu::llvmc::global_processor & module_a, mu::vector <mu::llvmc::skeleton::node *> & template_arguments_a) :
			parent (module_a.current_context),
			module (module_a),
			template_arguments (template_arguments_a)
			{
				module_a.current_context = this;
			}
			~process_template ()
			{
				assert (module.current_context == this);
				module.current_context = parent;
			}
			void node (mu::llvmc::ast::node * node_a) override
			{
				node_a->visit (parent);
			}
			void template_parameter (mu::llvmc::ast::template_parameter * node_a) override
			{
				assert (node_a->argument + 1 < template_arguments.size ());
				node_a->assigned = true;
				node_a->generated.push_back (template_arguments [node_a->argument + 1]);
			}
			mu::llvmc::ast::visitor * parent;
			mu::llvmc::global_processor & module;
			mu::vector <mu::llvmc::skeleton::node *> & template_arguments;
		};
    }
}

void mu::llvmc::function_processor::process_template (mu::llvmc::ast::expression * node_a)
{
	if (node_a->predicate_position == node_a->arguments.size ())
	{
		mu::vector <mu::llvmc::skeleton::node *> arguments;
		for (auto i (node_a->arguments.begin ()), j (node_a->arguments.end ()); i != j && error == nullptr; ++i)
		{
			auto value (*i);
			module_m.global_m.process_node (value);
			auto & nodes (value->generated);
			arguments.insert (arguments.end (), nodes.begin (), nodes.end ());
		}
		if (error == nullptr)
		{
			assert (arguments.size () > 0);
			auto template_l (mu::cast <mu::llvmc::skeleton::template_c> (arguments [0]));
			mu::llvmc::process_template processor (module_m.global_m, arguments);
			auto & target (node_a->generated);
			for (auto i (template_l->body.begin ()), j (template_l->body.end ()); i != j && error == nullptr; ++i)
			{
                auto orig (*i);
                mu::llvmc::clone_context context (template_l->base);
				auto value (orig->clone (context));
				module_m.global_m.process_node (value);
				auto & nodes (value->generated);
				target.insert (target.end (), nodes.begin (), nodes.end ());
			}
			if (error == nullptr)
			{
				node_a->assigned = true;
			}
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Template instantiations cannot have predicates", mu::core::error_type::template_instantiations_cannot_have_predicates, node_a->region);
	}
}

void mu::llvmc::global_processor::process_node (mu::llvmc::ast::node * node_a)
{
	assert (node_a != nullptr);
	if (!node_a->assigned)
	{
		node_a->visit (current_context);
	}
	assert ((error != nullptr) xor (node_a->assigned));
}

void mu::llvmc::function_processor::process_asm (mu::llvmc::ast::expression * asm_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (module_m.module_m->global);
	size_t predicate_offset (~0);
    process_call_values (asm_a->arguments, asm_a->predicate_position, arguments, most_specific_branch, predicate_offset);
    assert (dynamic_cast <mu::llvmc::skeleton::asm_c *> (arguments [0]) != nullptr);
    auto instruction (new (GC) mu::llvmc::skeleton::inline_asm (asm_a->region, most_specific_branch, arguments, predicate_offset));
	asm_a->assigned = true;
    asm_a->generated.push_back (instruction);
}

mu::llvmc::skeleton::number::number (uint64_t value_a) :
value (value_a)
{
}

mu::llvmc::skeleton::number * mu::llvmc::function_processor::process_number (mu::llvmc::ast::number * number_a)
{
	mu::llvmc::skeleton::number * result (nullptr);
	std::string data_l (number_a->number_m.begin (), number_a->number_m.end ());
	if (data_l.size () > 0)
	{
		auto prefix (data_l [0]);
		std::unique_ptr <uint8_t> remaining (new uint8_t [data_l.size () + 1]);
		uint64_t value;
		int parsed;
		switch (prefix)
		{
			case 'h':		
				parsed = sscanf (&data_l.c_str () [1], "%" PRIx64 " %s", &value, remaining.get ());
				break;
			case 'd':
				parsed = sscanf (&data_l.c_str () [1], "%" PRIu64 " %s", &value, remaining.get ());		
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				parsed = sscanf (&data_l.c_str () [0], "%" PRIu64 " %s", &value, remaining.get ());		
				break;
			case 'o':
				parsed = sscanf (&data_l.c_str () [1], "%" PRIo64 " %s", &value, remaining.get ());		
				break;
			default:
				parsed = 0;
				break;
		}
		if (parsed == 1)
		{
			result = new (GC) mu::llvmc::skeleton::number (value);
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Unable to convert string to number", mu::core::error_type::error_converting_string_to_number, number_a->region);
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Unable to convert string to number", mu::core::error_type::error_converting_string_to_number, number_a->region);
	}
	return result;
}

void mu::llvmc::function_processor::process_single_node (mu::llvmc::ast::node * node_a)
{
	assert (node_a != nullptr);
	module_m.global_m.process_node (node_a);
    auto size (node_a->generated.size ());
	if (error == nullptr && size != 1)
	{
		error = new (GC) mu::core::error_string (U"Expecting 1 value", mu::core::error_type::expecting_one_value, node_a->region);
	}
}

mu::llvmc::skeleton::value * mu::llvmc::function_processor::process_value (mu::llvmc::ast::node * node_a)
{
	assert (node_a != nullptr);
	mu::llvmc::skeleton::value * result (nullptr);
	process_single_node (node_a);
	if (error == nullptr)
	{
        auto & nodes (node_a->generated);
        assert (nodes.size () == 1);
		result = dynamic_cast <mu::llvmc::skeleton::value *> (nodes [0]);
		if (result == nullptr)
		{
			error = new (GC) mu::core::error_string (U"Node is not value", mu::core::error_type::node_is_not_a_value, node_a->region);
		}
	}
	return result;
}

mu::llvmc::skeleton::type * mu::llvmc::function_processor::process_type (mu::llvmc::ast::node * node_a)
{
	mu::llvmc::skeleton::type * result (nullptr);
	process_single_node (node_a);
	if (error == nullptr)
	{
		auto & nodes (node_a->generated);
        assert (nodes.size () == 1);
		result = dynamic_cast<mu::llvmc::skeleton::type *> (nodes [0]);
	}
	return result;
}

void mu::llvmc::function_processor::process_results ()
{
	mu::llvmc::branch_analyzer branches (module_m.module_m->global, error);
	node_m->for_each_results (
        [&]
        (mu::llvmc::ast::node * node_a, size_t index_a)
        {
            auto result_a (dynamic_cast <mu::llvmc::ast::result *> (node_a));
			if (result_a != nullptr)
			{
				auto type (process_type (result_a->written_type));
				if (type != nullptr)
				{
					auto value (process_value (result_a->value));
					if (value != nullptr)
					{
                        if (*type == *value->type ())
                        {
                            function_m->results.push_back (new (GC) mu::llvmc::skeleton::result (type, value));
                            branches.add_branch (value->branch, result_a->region);
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Actual result type does not match formal result type", mu::core::error_type::actual_formal_result_type_mismatch, result_a->region);
                        }
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_a_type, result_a->written_type->region);
				}
			}
			else
			{
				error = new (GC) mu::core::error_string (U"Expecting a result", mu::core::error_type::expecting_a_result, node_a->region);
			}
        },
        [&]
        (mu::llvmc::ast::node * node_a, size_t)
        {
            module_m.global_m.process_node (node_a);
            if (error == nullptr)
            {
                for (auto i : node_a->generated)
                {
                    auto value (dynamic_cast <mu::llvmc::skeleton::value *> (i));
                    if (value != nullptr)
                    {
                        function_m->results.push_back (i);
                        branches.add_branch (static_cast <mu::llvmc::skeleton::value *> (i)->branch, node_a->region);
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Predicate is not a value", mu::core::error_type::expecting_a_value, node_a->region);
                    }
                }
            }
        },
        [&]
        (mu::llvmc::ast::node *, size_t)
        {
            function_m->predicate_offsets.push_back (function_m->results.size ());
        },
        [&]
        (mu::llvmc::ast::node *, size_t)
        {
			branches.new_set ();
            function_m->branch_ends.push_back (function_m->results.size ());
        },
        [&]
        ()
        {
            return error == nullptr;
        }
	);
}

void mu::llvmc::function_processor::process_identity (mu::llvmc::ast::expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (module_m.module_m->global);
	size_t predicate_offset (~0);
	process_call_values (expression_a->arguments, expression_a->predicate_position, arguments, most_specific_branch, predicate_offset);
    auto source (new (GC) mu::llvmc::skeleton::identity_call (arguments, predicate_offset, &module_m.module_m->the_unit_type));
    switch (predicate_offset)
    {
        case 0:
            assert (false);
            break;
        case 1:
        {
            auto element (new (GC) mu::llvmc::skeleton::identity_element (most_specific_branch, source, &module_m.module_m->the_unit_type));
            source->elements.push_back (element);
            expression_a->generated.push_back (element);
            break;
        }
        default:
        {
            auto & values (expression_a->generated);
            for (size_t i (1); i < predicate_offset; ++i)
            {
                auto element (new (GC) mu::llvmc::skeleton::identity_element (most_specific_branch, source, mu::cast <mu::llvmc::skeleton::value> (values [i])->type ()));
                source->elements.push_back (element);
                values.push_back (element);
            }
            break;
        }
    }
    if (predicate_offset == 2)
    {
    }
    else
    {
        auto & results (expression_a->generated);
        results.insert (results.end (), arguments.begin () + 1, arguments.begin () + predicate_offset);
    }
}

void mu::llvmc::function_processor::process_value_call (mu::llvmc::ast::expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (entry_m);
	size_t predicate_offset (~0);
	process_call_values (expression_a->arguments, expression_a->predicate_position, arguments, most_specific_branch, predicate_offset);
	auto target (static_cast<mu::llvmc::skeleton::value *> (arguments [0]));
	auto type_l (target->type ());
	auto pointer_type (dynamic_cast<mu::llvmc::skeleton::pointer_type *> (type_l));
	if (pointer_type != nullptr)
	{
		auto function_type (dynamic_cast<mu::llvmc::skeleton::function_type *> (pointer_type->pointed_type));
		if (function_type != nullptr)
		{
			assert (predicate_offset <= arguments.size ());
			auto k (arguments.begin () + 1);
			auto l (arguments.begin () + predicate_offset);
			size_t i (0);
			size_t j (function_type->function->parameters.size ());
			for (; i != j && k != l && error == nullptr; ++i, ++k)
			{
				auto argument_value (dynamic_cast<mu::llvmc::skeleton::value *> (*k));
				if (argument_value != nullptr)
				{
					if ((*argument_value->type ()) != *function_type->function->parameters [i]->type ())
					{
						error = new (GC) mu::core::error_string (U"Argument type does not match parameter type", mu::core::error_type::argument_type_does_not_match_parameter_type, expression_a->region);
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Argument to function is not a value", mu::core::error_type::argument_to_function_is_not_a_value, expression_a->region);
				}
			}
			if (error == nullptr)
			{
				if ((i == j) == (k == l))
				{
					if (!arguments.empty ())
					{
						auto call (new (GC) mu::llvmc::skeleton::function_call (function_type->function, most_specific_branch, arguments, predicate_offset, &module_m.module_m->the_unit_type));
						mu::vector <mu::llvmc::skeleton::node *> returned_results;
                        mu::llvmc::skeleton::branch * branch;
                        if (function_type->function->branch_ends.size () < 2)
                        {
                            branch = most_specific_branch;
                        }
                        else
                        {
                            branch = new (GC) mu::llvmc::skeleton::branch (most_specific_branch);
                        }
						auto empty (true);
						function_type->function->for_each_results (
							[&]
							(mu::llvmc::skeleton::result * node_a, size_t index_a)
							{
                                auto element (new (GC) mu::llvmc::skeleton::call_element (expression_a->region, branch, call, node_a->type));
								returned_results.push_back (element);
                                call->elements.push_back (element);
								empty = false;
							},
							mu::llvmc::skeleton::function::empty_node,
							[&]
							(mu::llvmc::skeleton::node * node_a, size_t index_a)
							{
								if (empty)
								{
                                    auto element (new (GC) mu::llvmc::skeleton::call_element (expression_a->region, branch, call, &module_m.module_m->the_unit_type));
									returned_results.push_back (element);
                                    call->elements.push_back (element);
								}
							},
							[&]
							(mu::llvmc::skeleton::node * node_a, size_t)
							{
								branch = new (GC) mu::llvmc::skeleton::branch (most_specific_branch);
								empty = true;
							}
						);
						expression_a->assigned = true;
                        switch (returned_results.size ())
                        {
                            case 0:
                            {
                                auto element (new (GC) mu::llvmc::skeleton::call_element (expression_a->region, most_specific_branch, call, &module_m.module_m->the_unit_type));
                                expression_a->generated.push_back (element);
                                call->elements.push_back (element);
                                break;
                            }
                            case 1:
                            {
                                expression_a->generated.push_back (returned_results [0]);
                                break;
                            }
                            default:
                            {
                                auto & target (expression_a->generated);
                                target.insert (target.end (), returned_results.begin (), returned_results.end ());
                                break;
                            }
                        }
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Incorrect number of arguments", mu::core::error_type::incorrect_number_of_arguments, expression_a->region);
				}
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Pointer does not point to a function", mu::core::error_type::pointer_does_not_point_to_a_function, expression_a->region);
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Only function pointers can be the target of a call", mu::core::error_type::only_function_pointers_can_be_target_of_call, expression_a->region);
	}
	module_m.current_expression_generation.erase (expression_a);
}

void mu::llvmc::function_processor::process_call_values (mu::vector <mu::llvmc::ast::node *> const & arguments, size_t predicate_offset, mu::vector <mu::llvmc::skeleton::node *> & arguments_a, mu::llvmc::skeleton::branch * & most_specific_branch, size_t & predicate_position_a)
{
    mu::llvmc::branch_analyzer branches (most_specific_branch, error);
	size_t predicate_position_l (~0);
	mu::llvmc::ast::for_each_argument (
		arguments,
		predicate_offset,
		[&]
		(mu::llvmc::ast::node * node_a, size_t index)
		{
			module_m.global_m.process_node (node_a);
			if (error == nullptr)
			{
                auto & nodes (node_a->generated);
                for (auto k (nodes.begin ()), l (nodes.end ()); k != l && error == nullptr; ++k)
                {
                    auto node (*k);
                    auto value (dynamic_cast<mu::llvmc::skeleton::value *> (node));
                    if (value != nullptr)
                    {
                        most_specific_branch = branches.add_branch (value->branch, node_a->region);
                    }
                    arguments_a.push_back (node);
                }
			}
		},
		[&]
		(mu::llvmc::ast::node * node_a, size_t index)
		{
			module_m.global_m.process_node (node_a);
			if (error == nullptr)
			{
                auto & nodes (node_a->generated);
                for (auto k (nodes.begin ()), l (nodes.end ()); k != l && error == nullptr; ++k)
                {
                    auto node (*k);
                    auto value (dynamic_cast<mu::llvmc::skeleton::value *> (node));
                    if (value != nullptr)
                    {
                        most_specific_branch = branches.add_branch (value->branch, node_a->region);
                    }
                    arguments_a.push_back (node);
                }
			}
		},
		[&]
		(mu::llvmc::ast::node * node_a, size_t index)
		{
            assert (predicate_position_l == ~0);
			predicate_position_l = arguments_a.size ();
		},
		[&]
		()
		{
			return error == nullptr;
		}
	);
	if (predicate_position_l == ~0)
	{
		predicate_position_l = arguments_a.size ();
	}
	predicate_position_a = predicate_position_l;
}

void mu::llvmc::function_processor::process_binary_integer_instruction (mu::llvmc::ast::expression * expression_a, size_t predicate_offset, mu::vector <mu::llvmc::skeleton::node *> const & arguments, mu::llvmc::skeleton::branch * most_specific_branch)
{
	if (predicate_offset == 3)
	{
		auto left (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [1]));
		if (left != nullptr)
		{
			auto right (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [2]));
			if (right != nullptr)
			{
				auto left_type (dynamic_cast<mu::llvmc::skeleton::integer_type *> (left->type ()));
				if (left_type != nullptr)
				{
					auto right_type (dynamic_cast<mu::llvmc::skeleton::integer_type *> (right->type ()));
					if (right_type != nullptr)
					{
						if (*left_type == *right_type)
						{
							expression_a->assigned = true;
							expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
						}
						else
						{
							error = new (GC) mu::core::error_string (U"Instruction left and right arguments must be same width", mu::core::error_type::instruction_arguments_must_have_same_bit_width, expression_a->region);
						}
					}
					else
					{
						error = new (GC) mu::core::error_string (U"Instruction right argument must be an integer type", mu::core::error_type::instruction_arguments_must_be_integers, expression_a->region);
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Instruction left argument must be an integer type", mu::core::error_type::instruction_arguments_must_be_integers, expression_a->region);
				}
			}
			else
			{
				error = new (GC) mu::core::error_string (U"Instruction right argument must be a value", mu::core::error_type::instruction_arguments_must_be_values, expression_a->region);
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Instruction left argument must be a value", mu::core::error_type::instruction_arguments_must_be_values, expression_a->region);
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Instruction expects two arguments", mu::core::error_type::instruction_expects_two_arguments, expression_a->region);
	}
}

void mu::llvmc::function_processor::process_marker (mu::llvmc::ast::expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (module_m.module_m->global);
	size_t predicate_offset (~0);
	process_call_values (expression_a->arguments, expression_a->predicate_position, arguments, most_specific_branch, predicate_offset);
    auto result (false);
    if (error == nullptr)
    {
        auto marker (static_cast<mu::llvmc::skeleton::marker *> (arguments [0]));
        switch (marker->type)
        {
            case mu::llvmc::instruction_type::add:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::alloca:
            {
                if (predicate_offset == 2)
                {
                    auto type (dynamic_cast <mu::llvmc::skeleton::type *> (arguments [1]));
                    if (type != nullptr)
                    {
						expression_a->assigned = true;
                        expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Alloca instruction expects its argument to be a type", mu::core::error_type::alloca_argument_type, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Alloca instruction expects one argument", mu::core::error_type::alloca_expects_one_argument, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::and_i:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::ashr:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::asm_i:
            {
                if (predicate_offset >= 2)
                {
                    auto asm_l (dynamic_cast <mu::llvmc::skeleton::asm_c *> (arguments [1]));
                    if (asm_l != nullptr)
                    {
                        size_t end (predicate_offset);
                        for (size_t i (2); i < end && error == nullptr; ++i)
                        {
                            auto value (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [i]));
                            if (value == nullptr)
                            {
                                error = new (GC) mu::core::error_string (U"Inline asm requires value arguments", mu::core::error_type::inline_asm_requires_values, expression_a->region);
                            }
                        }
                    }
                    else
                    {
                        assert (false);
                    }
                }
                break;
            }
            case mu::llvmc::instruction_type::bitcast:
            {
                if (predicate_offset >= 3)
                {
                    auto value (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]));
                    if (value != nullptr)
                    {
                        auto type (dynamic_cast <mu::llvmc::skeleton::type *> (arguments [2]));
                        if (type != nullptr)
                        {
                            auto value_pointer (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (value->type ()));
                            if (value_pointer != nullptr)
                            {
                                auto type_pointer (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (type));
                                if (type_pointer != nullptr)
                                {
									expression_a->assigned = true;
                                    expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Second argument to bitcast must be a pointer type", mu::core::error_type::argument_must_be_pointer_type, expression_a->region);
                                }
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"First argument to bitcast must be a pointer type", mu::core::error_type::argument_must_be_pointer_type, expression_a->region);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Second argument to bitcast must be a type", mu::core::error_type::expecting_a_type, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"First argument to bitcast must be a value", mu::core::error_type::instruction_arguments_must_be_values, expression_a->region);
                    }
                }
                break;
            }
            case mu::llvmc::instruction_type::cmpxchg:
            {
                if (predicate_offset == 4)
                {
                    auto one (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]));
                    if (one != nullptr)
                    {
                        auto two (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]));
                        if (two != nullptr)
                        {
                            auto three (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [3]));
                            if (three != nullptr)
                            {
                                auto one_type (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (one->type()));
                                if (one_type != nullptr)
                                {
                                    if (*one_type->pointed_type == *two->type ())
                                    {
                                        if (*one_type->pointed_type == *three->type ())
                                        {
											expression_a->assigned = true;
                                            expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                                        }
                                        else
                                        {
                                            error = new (GC) mu::core::error_string (U"Cmpxchg requires argument one to point to type of argument three", mu::core::error_type::cmpxchg_one_point_three, expression_a->region);
                                        }
                                    }
                                    else									
                                    {
                                        error = new (GC) mu::core::error_string (U"Cmpxchg requires argument one to point to type of argument two", mu::core::error_type::cmpxchg_one_point_two, expression_a->region);
                                    }
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Cmpxchg requires argument one to be a pointer", mu::core::error_type::cmpxchg_argument_one_pointer, expression_a->region);
                                }
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"Cmpxchg requires arguments to be values", mu::core::error_type::instruction_arguments_must_be_values, expression_a->region);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Cmpxchg requires arguments to be values", mu::core::error_type::instruction_arguments_must_be_values, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Cmpxchg requires arguments to be values", mu::core::error_type::instruction_arguments_must_be_values, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Cmpxchg requires three arguments", mu::core::error_type::cmpxchg_requires_three_arguments, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::extractvalue:
            {
                if (predicate_offset == 3)
                {
                    auto aggregate (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]));
                    if (aggregate != nullptr)
                    {
                        auto struct_l (dynamic_cast <mu::llvmc::skeleton::struct_type *> (aggregate->type ()));
                        if (struct_l != nullptr)
                        {
                            auto index (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (arguments [2]));
                            if (index != nullptr)
                            {
                                if (index->value_m < struct_l->elements.size ())
                                {
									expression_a->assigned = true;
                                    expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Extractvalue index is out of range", mu::core::error_type::index_out_of_bounds, expression_a->region);
                                }
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"Extractvalue requires second argument to be a constant", mu::core::error_type::expecting_a_constant, expression_a->region);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Exctractvalue requires first argument to be an aggregate type", mu::core::error_type::expecting_an_aggregate, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Exctractvalue requires first arguments to be a values", mu::core::error_type::expecting_a_value, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Extractvalue requires two arguments", mu::core::error_type::incorrect_number_of_arguments, expression_a->region);
                }
                break;
            }
			case mu::llvmc::instruction_type::getelementptr:
			{
				if (predicate_offset >= 3)
				{
					auto ptr (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]));
					if (ptr != nullptr)
					{
						auto ptr_index (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]));
						if (ptr_index != nullptr)
						{							
							auto ptr_type (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (ptr->type ()));
							if (ptr_type != nullptr)
							{
								auto ptr_index_type (dynamic_cast <mu::llvmc::skeleton::integer_type  *> (ptr_index->type ()));
								if (ptr_index_type != nullptr)
								{
									for (auto i (arguments.begin () + 3), j (arguments.begin () + predicate_offset); i != j && error == nullptr; ++i)
									{
										auto index (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (*i));
										if (index != nullptr)
										{
											if (mu::cast <mu::llvmc::skeleton::integer_type> (index->type ())->bits != 32)
											{
												error = new (GC) mu::core::error_string (U"Getelementptr requires trailing index types to be 32bit integers", mu::core::error_type::getelementptr_trailing_32bit, expression_a->region);
											}
										}
										else
										{
											error = new (GC) mu::core::error_string (U"Getelementptr requires trailing indicies to be constant integers", mu::core::error_type::getelementptr_trailing_constant, expression_a->region);
										}
									}
									if (error == nullptr)
									{
										expression_a->assigned = true;
										expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
									}
								}
								else
								{
									error = new (GC) mu::core::error_string (U"Getelementptr requires pointer index to be an integer", mu::core::error_type::getelementptr_first_argument_integer_type, expression_a->region);
								}
							}
							else
							{
								error = new (GC) mu::core::error_string (U"Getelementptr first argument must be a pointer", mu::core::error_type::getelementptr_requires_pointer_type, expression_a->region);
							}
						}
						else
						{
							error = new (GC) mu::core::error_string (U"Getelementptr requires its arguments to be values", mu::core::error_type::getelementptr_requires_values, expression_a->region);							
						}
					}
					else
					{
						error = new (GC) mu::core::error_string (U"Getelementptr requires its arguments to be values", mu::core::error_type::getelementptr_requires_values, expression_a->region);
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Getelementptr requires at least two arguments", mu::core::error_type::getelementptr_requires_two, expression_a->region);
				}
				break;
			}
            case mu::llvmc::instruction_type::icmp:
            {
                if (predicate_offset == 4)
                {
                    auto predicate (dynamic_cast <mu::llvmc::skeleton::predicate *> (arguments [1]));
                    if (predicate != nullptr)
                    {
                        auto left (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]));
                        if (left != nullptr)
                        {
                            auto right (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [3]));
                            if (right != nullptr)
                            {
                                auto left_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (left->type ()));
                                if (left_type != nullptr)
                                {
                                    if (*left->type () == *right->type ())
                                    {
                                        auto icmp (new (GC) mu::llvmc::skeleton::icmp (expression_a->region, most_specific_branch, &module_m.module_m->integer_1_type, predicate, left, right));
                                        icmp->predicates.assign (arguments.begin () + 4, arguments.end ());
										expression_a->assigned = true;
                                        expression_a->generated.push_back (icmp);
                                    }
                                    else
                                    {
                                        error = new (GC) mu::core::error_string (U"ICMP arguments must be the same type", mu::core::error_type::icmp_arguments_same_type, expression_a->region);
                                    }
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"ICMP arguments must be integers", mu::core::error_type::icmp_arguments_integers, expression_a->region);
                                }
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"ICMP right argument must be a value", mu::core::error_type::icmp_right_argument_value, expression_a->region);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"ICMP left argument must be a value", mu::core::error_type::icmp_left_argument_value, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"ICMP first argument must be predicate", mu::core::error_type::icmp_first_argument_predicate, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"ICMP instruction expects a predicate and two arguments", mu::core::error_type::icmp_expects_predicate_two_arguments, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::if_i:
            {
                if (predicate_offset == 2)
                {
                    auto predicate (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [1]));
                    if (predicate != nullptr)
                    {
                        auto integer_type (dynamic_cast<mu::llvmc::skeleton::integer_type *> (predicate->type ()));
                        if (integer_type != nullptr)
                        {
                            if (integer_type->bits == 1)
                            {
                                result = true;
                                auto false_const (new (GC) mu::llvmc::skeleton::constant_integer (expression_a->region, module_m.module_m->global, 1, 0));
                                auto true_const (new (GC) mu::llvmc::skeleton::constant_integer (expression_a->region, module_m.module_m->global, 1, 1));
                                arguments.push_back (false_const);
                                arguments.push_back (true_const);
                                auto switch_i (new (GC) mu::llvmc::skeleton::switch_i (most_specific_branch, arguments, &module_m.module_m->the_unit_type));
                                auto true_branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
                                auto false_branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
                                auto true_element (new (GC) mu::llvmc::skeleton::switch_element (expression_a->region, true_branch, switch_i, true_const));
                                auto false_element (new (GC) mu::llvmc::skeleton::switch_element (expression_a->region, false_branch, switch_i, false_const));
								expression_a->assigned = true;
                                auto & values (expression_a->generated);
                                values.push_back (true_element);
                                values.push_back (false_element);
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"If instruction expects 1 bit integer", mu::core::error_type::if_instruction_expects_one_bit_integer, expression_a->region);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"If instruction expects an integer type value", mu::core::error_type::if_instruction_expects_integer_type_value, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"If instruction expects a value argument", mu::core::error_type::if_instruction_expects_a_value_argument, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"If instruction expects one argument", mu::core::error_type::if_instruction_expects_one_argument, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::insertvalue:
            {
                if (predicate_offset >= 4)
                {
                    auto struct_l (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]));
                    if (struct_l != nullptr)
                    {
                        auto value (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]));
                        if (value != nullptr)
                        {                            
                            auto current_aggregate (struct_l->type ());
                            for (size_t current_index (3); current_index < predicate_offset && error == nullptr; ++current_index)
                            {
                                auto type (dynamic_cast <mu::llvmc::skeleton::struct_type *> (current_aggregate));
                                if (type != nullptr)
                                {
                                    auto position (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (arguments [3]));
                                    if (position != nullptr)
                                    {
                                        if (position->value_m < type->elements.size ())
                                        {
                                            current_aggregate = type->elements [position->value_m];
                                        }
                                        else
                                        {
                                            error = new (GC) mu::core::error_string (U"Aggregate has no element at this index", mu::core::error_type::index_out_of_bounds, expression_a->region);
                                        }
                                    }
                                    else
                                    {
                                        error = new (GC) mu::core::error_string (U"Value is not an aggregate at this index", mu::core::error_type::expecting_an_aggregate, expression_a->region);
                                    }
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Insertvalue requires first value to be a struct type", mu::core::error_type::expecting_value_to_be_struct, expression_a->region);
                                }
                            }
                            if (error == nullptr)
                            {
                                if (*current_aggregate == *value->type ())
                                {
									expression_a->assigned = true;
                                    expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Insertvalue value does not match type of aggregate", mu::core::error_type::value_does_not_match_aggregate, expression_a->region);
                                }
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Insertvalue second argument must be a value", mu::core::error_type::expecting_a_value, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Insertvalue instruction requires first argument to be a value", mu::core::error_type::expecting_a_value, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Insertvalue instruction requires three arguments", mu::core::error_type::insertvalue_expects_three_arguments, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::inttoptr:
            {
                if (predicate_offset == 3)
                {
                    auto value (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]));
                    if (value != nullptr)
                    {
                        auto integer (dynamic_cast <mu::llvmc::skeleton::integer_type *> (value->type ()));
                        if (integer != nullptr)
                        {
                            auto type (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (arguments [2]));
                            if (type != nullptr)
                            {
								expression_a->assigned = true;
                                expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"Ptrfromint instruction requires second argument to be a pointer type", mu::core::error_type::expecting_integer_type, expression_a->region);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Ptrfromint source must be an integer", mu::core::error_type::expecting_integer_type, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Ptrfromint instruction requires first argument to be value", mu::core::error_type::expecting_a_value, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Ptrfromint instruction requires two arguments", mu::core::error_type::ptr_to_int_expects_two, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::load:
            {
                if (predicate_offset == 2)
                {
                    auto source (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [1]));
                    if (source != nullptr)
                    {
                        auto type (dynamic_cast<mu::llvmc::skeleton::pointer_type *> (source->type ()));
                        if (type != nullptr)
                        {
							expression_a->assigned = true;
                            expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Load argument must be a pointer type", mu::core::error_type::load_argument_pointer_type, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Load argument must be a value", mu::core::error_type::load_argument_must_be_values, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Load instruction expects two arguments", mu::core::error_type::load_expects_one_argument, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::lshr:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::mul:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::or_i:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::ptrtoint:
            {
                if (predicate_offset == 3)
                {
                    auto value (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]));
                    if (value != nullptr)
                    {
                        auto pointer (dynamic_cast <mu::llvmc::skeleton::pointer_type *> (value->type ()));
                        if (pointer != nullptr)
                        {
                            auto type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (arguments [2]));
                            if (type != nullptr)
                            {
								expression_a->assigned = true;
                                expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"Ptrtoint instruction requires second argument to be an integer type", mu::core::error_type::expecting_integer_type, expression_a->region);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Ptrtoint source must be a pointer", mu::core::error_type::expecting_pointer_type, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Ptrtoint instruction requires first argument to be value", mu::core::error_type::expecting_a_value, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Ptrtoint instruction requires two arguments", mu::core::error_type::ptr_to_int_expects_two, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::sdiv:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::select:
            {
				if (predicate_offset == 4)
				{
					auto predicate (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]));
					if (predicate != nullptr)
					{
						auto predicate_type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (predicate->type ()));
						if (predicate_type != nullptr)
						{
							if (predicate_type->bits == 1)
							{
								auto left (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [2]));
								if (left != nullptr)
								{
									auto right (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [3]));
									if (right != nullptr)
									{
										if (*left->type () == *right->type ())
										{
											expression_a->assigned = true;
											expression_a->generated.push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
										}
										else
										{
											error = new (GC) mu::core::error_string (U"Select second and third arguments must be the same type", mu::core::error_type::select_arguments_same_type, expression_a->region);
										}
									}
									else
									{
										error = new (GC) mu::core::error_string (U"Select third argument must be a value", mu::core::error_type::expecting_a_value, expression_a->region);
									}
								}
								else
								{
									error = new (GC) mu::core::error_string (U"Select second argument must be a value", mu::core::error_type::expecting_a_value, expression_a->region);
								}
							}
							else
							{
								error = new (GC) mu::core::error_string (U"Select first argument must be one bit", mu::core::error_type::expecting_one_bit_integer, expression_a->region);
							}
						}
						else
						{
							error = new (GC) mu::core::error_string (U"Select first argument must be an integer", mu::core::error_type::expecting_integer_type, expression_a->region);
						}
					}
					else
					{
						error = new (GC) mu::core::error_string (U"Select first argument must be a value", mu::core::error_type::expecting_a_value, expression_a->region);
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Select instruction requires three arguments", mu::core::error_type::select_three_arguments, expression_a->region);
				}
                break;
            }
            case mu::llvmc::instruction_type::shl:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::srem:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::store:
            {
                if (predicate_offset == 3)
                {
                    auto source (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [1]));
                    if (source != nullptr)
                    {
                        auto destination (dynamic_cast<mu::llvmc::skeleton::value *> (arguments [2]));
                        if (destination != nullptr)
                        {
                            auto destination_type (dynamic_cast<mu::llvmc::skeleton::pointer_type *> (destination->type ()));
                            if (destination_type != nullptr)
                            {
                                if (*destination_type->pointed_type == *source->type ())
                                {
                                    auto store (new (GC) mu::llvmc::skeleton::store (expression_a->region, most_specific_branch, &module_m.module_m->the_unit_type, source, destination));
                                    store->predicates.assign (arguments.begin () + 3, arguments.end ());
									expression_a->assigned = true;
                                    expression_a->generated.push_back (store);
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Type pointed to by store right argument does not match type of left argument", mu::core::error_type::store_right_pointed_type_doesnt_match_left, expression_a->region);
                                }
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"Store right argument must be a pointer type", mu::core::error_type::store_right_argument_pointer_type, expression_a->region);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Store right argument must be a value", mu::core::error_type::store_arguments_must_be_values, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Store left argument must be a value", mu::core::error_type::store_arguments_must_be_values, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Store instruction expects two arguments", mu::core::error_type::store_expects_two_arguments, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::switch_i:
            {
                if (predicate_offset > 1)
                {
                    auto input (dynamic_cast <mu::llvmc::skeleton::value *> (arguments [1]));
                    if (input != nullptr)
                    {
                        auto type (dynamic_cast <mu::llvmc::skeleton::integer_type *> (input->type ()));
                        if (type != nullptr)
                        {
                            std::set <uint64_t> used;
                            for (auto i (arguments.begin () + 2), j (arguments.begin () + predicate_offset); i != j && error == nullptr; ++i)
                            {
                                auto constant (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (*i));
                                if (constant != nullptr)
                                {
                                    if (*constant->type () != *type)
                                    {
                                        error = new (GC) mu::core::error_string (U"Switch requires case arguments to be same type as input", mu::core::error_type::switch_requires_matching_case_types, expression_a->region);
                                    }
                                    auto existing (used.find (constant->value_m));
                                    if (existing != used.end ())
                                    {
                                        error = new (GC) mu::core::error_string (U"Switch requires case arguments to be unique", mu::core::error_type::switch_requires_unique_case, expression_a->region);
                                    }
                                    used.insert (constant->value_m);
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Switch requires case arguments to be constant integers", mu::core::error_type::switch_requires_case_constant, expression_a->region);
                                }
                            }
                            if (error == nullptr)
                            {
                                result = true;
								expression_a->assigned = true;
                                auto & values (expression_a->generated);
                                auto switch_i (new (GC) mu::llvmc::skeleton::switch_i (most_specific_branch, arguments, &module_m.module_m->the_unit_type));
                                for (auto i (switch_i->arguments.begin () + 2), j (switch_i->arguments.begin () + predicate_offset); i != j; ++i)
                                {
                                    auto branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
                                    assert (dynamic_cast <mu::llvmc::skeleton::constant_integer *> (*i) != nullptr);
                                    auto element (new (GC) mu::llvmc::skeleton::switch_element (expression_a->region, branch, switch_i, static_cast <mu::llvmc::skeleton::constant_integer *> (*i)));
                                    values.push_back (element);
                                }
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Switch requires input to be an integer", mu::core::error_type::switch_requires_integer, expression_a->region);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Switch requires input to be a value", mu::core::error_type::switch_requires_value, expression_a->region);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Switch requires an input argument", mu::core::error_type::switch_requires_input, expression_a->region);
                }
                break;
            }
            case mu::llvmc::instruction_type::sub:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::typeof_i:
            {
                assert (false);
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::udiv:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::urem:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            case mu::llvmc::instruction_type::xor_i:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
                break;
            }
            default:
                assert (false);
                break;
        }
    }
	assert ((error != nullptr) xor (expression_a->assigned));
}

mu::llvmc::function_processor::function_processor (mu::llvmc::module_processor & module_a, mu::core::error * & error_a, mu::llvmc::skeleton::branch * entry_a, mu::llvmc::ast::function * node_a) :
module_m (module_a),
function_m (new (GC) mu::llvmc::skeleton::function (node_a->region, module_m.module_m->global)),
node_m (node_a),
error (error_a),
entry_m (entry_a),
parent (module_a.global_m.current_context)
{
	module_a.global_m.current_context = this;
}

mu::llvmc::function_processor::~function_processor ()
{
	module_m.global_m.current_context = parent;
}

void mu::llvmc::module_processor::set (mu::llvmc::ast::set * node_a)
{
	for (auto i: node_a->nodes)
	{
		global_m.process_node (i);
		node_a->generated.insert (node_a->generated.end (), i->generated.begin (), i->generated.end ());
	}
	if (global_m.error == nullptr)
	{
		node_a->assigned = true;
	}
}

class namespace_extractor : public mu::llvmc::skeleton::namespace_visitor
{
public:
    namespace_extractor (mu::core::error * & error_a, mu::llvmc::ast::namespace_c * node_a) :
    error (error_a),
    node (node_a)
    {
        assert (node_a->node_m->assigned);
    }
    mu::core::error * & error;
    mu::llvmc::ast::namespace_c * node;
    void named (mu::llvmc::skeleton::namespace_container * namespace_a) override
    {
        auto element ((*namespace_a) [node->member]);
        if (element != nullptr)
        {
            node->assigned = true;
            node->generated.push_back (element);
        }
        else
        {
            error = new (GC) mu::core::error_string (U"Namespace container does not have member with stated name", mu::core::error_type::not_a_member);
        }
    }
    void unnamed () override
    {
        error = new (GC) mu::core::error_string (U"Node is not a namespace container", mu::core::error_type::not_a_namespace_container);
    }
};

void mu::llvmc::function_processor::namespace_c (mu::llvmc::ast::namespace_c * node_a)
{
    module_m.global_m.process_node (node_a->node_m);
    if (error == nullptr)
    {
        assert (node_a->node_m->assigned);
        if (node_a->node_m->generated.size () == 1)
        {
            namespace_extractor extractor (error, node_a);
            node_a->node_m->generated [0]->named (&extractor);
        }
        else
        {
            error = new (GC) mu::core::error_string (U"Can only extract name from one node", mu::core::error_type::can_only_extract_from_one);
        }
    }
}