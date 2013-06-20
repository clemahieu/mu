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

mu::llvmc::module_result mu::llvmc::analyzer::analyze (mu::llvmc::ast::node * module_a)
{
	mu::llvmc::analyzer_module analyzer_l;
	auto result (analyzer_l.analyze (module_a));
	return result;
}

mu::llvmc::analyzer_module::analyzer_module () :
result_m ({nullptr, nullptr})
{
}

mu::llvmc::analyzer_function::analyzer_function (mu::llvmc::analyzer_module & module_a) :
result_m ({nullptr, nullptr}),
module (module_a)
{
}

void mu::llvmc::analyzer_function::process_parameters (mu::llvmc::analyzer_node & nodes, mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s)
{
	for (auto k (function_a->parameters.begin ()), l (function_a->parameters.end ()); k != l && result_m.error == nullptr; ++k)
	{
		auto type_l (nodes.process_type ((*k)->type));
		if (type_l != nullptr)
		{
			auto parameter_s (new (GC) mu::llvmc::skeleton::parameter ((*k)->region, function_s->entry, type_l, (*k)->name));
			module.already_generated [*k].push_back (parameter_s);
			function_s->parameters.push_back (parameter_s);
		}
		else
		{
			result_m.error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_type_in_parameters);
		}
	}
}

void mu::llvmc::analyzer_node::process_node (mu::llvmc::ast::node * node_a)
{
	assert (node_a != nullptr);
	auto existing (module.already_generated.find (node_a));
	if (existing == module.already_generated.end ())
	{
		auto definite_expression (dynamic_cast<mu::llvmc::ast::definite_expression *> (node_a));
		if (definite_expression != nullptr)
		{
			process_definite_expression (definite_expression);
		}
		else
		{
			auto value_node (dynamic_cast <mu::llvmc::ast::value *> (node_a));
			if (value_node != nullptr)
			{
				auto value (dynamic_cast <mu::llvmc::skeleton::value *> (value_node->node_m));
				if (value != nullptr)
				{
					assert (value->branch == nullptr);
					value->branch = module.module->global;
				}
				module.already_generated [node_a].push_back (value_node->node_m);
			}
			else
			{
				auto element_node (dynamic_cast<mu::llvmc::ast::element *> (node_a));
				if (element_node != nullptr)
				{
					process_element (element_node);
				}
				else
				{
					auto unit_node (dynamic_cast<mu::llvmc::ast::unit *> (node_a));
					if (unit_node != nullptr)
					{
						module.already_generated [node_a].push_back (new (GC) mu::llvmc::skeleton::unit_value (module.module->global));
					}
					else
					{
						auto set (dynamic_cast<mu::llvmc::ast::set_expression *> (node_a));
						if (set != nullptr)
						{
							auto & values (module.already_generated [node_a]);
							for (auto i : set->items)
							{
								process_node (i);
								auto & values_l (module.already_generated [i]);
								values.insert (values.end (), values_l.begin (), values_l.end ());
							}
						}
						else
						{
							auto integer_type (dynamic_cast<mu::llvmc::ast::integer_type *> (node_a));
							if (integer_type != nullptr)
							{
								process_integer_type (integer_type);
							}
							else
							{
								auto pointer_type (dynamic_cast<mu::llvmc::ast::pointer_type *> (node_a));
								if (pointer_type != nullptr)
								{
									process_pointer_type (pointer_type);
								}
								else
								{
									auto constant_int (dynamic_cast <mu::llvmc::ast::constant_int *> (node_a));
									if (constant_int != nullptr)
									{
										process_constant_int (constant_int);
									}
									else
									{
										auto loop (dynamic_cast<mu::llvmc::ast::loop *> (node_a));
										if (loop != nullptr)
										{
											process_loop (loop);
										}
										else
										{
											auto asm_l (dynamic_cast <mu::llvmc::ast::asm_c *> (node_a));
											if (asm_l != nullptr)
											{
												auto type (process_type (asm_l->type));
												if (type != nullptr)
												{
													module.already_generated [node_a].push_back (new (GC) mu::llvmc::skeleton::asm_c (type, asm_l->text, asm_l->constraints));
												}
												else
												{
													error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_a_type, asm_l->type->region);
												}
											}
											else
											{
												auto number (dynamic_cast <mu::llvmc::ast::number *> (node_a));
												if (number != nullptr)
												{
													error = new (GC) mu::core::error_string (U"Numbers must be parsed by a keyword", mu::core::error_type::numbers_parsed_by_keyword);
												}
												else
												{
													auto array_type (dynamic_cast <mu::llvmc::ast::array_type *> (node_a));
													if (array_type != nullptr)
													{
														process_array_type (array_type);
													}
													else
													{
														auto constant_array (dynamic_cast <mu::llvmc::ast::constant_array *> (node_a));
														if (constant_array != nullptr)
														{
															process_constant_array (constant_array);
														}
														else
														{
                                                            auto function_node (dynamic_cast<mu::llvmc::ast::function *> (node_a));
                                                            if (function_node != nullptr)
                                                            {
                                                                analyzer_function analyzer (module);
                                                                analyzer.analyze (function_node);
                                                                error = analyzer.result_m.error;
                                                            }
                                                            else
															{
																std::string name (typeid (*node_a).name ());
																assert (false);
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	assert (error != nullptr || (module.already_generated.find (node_a) != module.already_generated.end ()));
}

void mu::llvmc::analyzer_node::process_constant_array (mu::llvmc::ast::constant_array * array_a)
{
    auto type (process_type (array_a->type));
    if (type != nullptr)
    {
        mu::vector <mu::llvmc::skeleton::constant *> initializer;
        for (auto i (array_a->initializer.begin ()), j (array_a->initializer.end ()); i != j && error == nullptr; ++i)
        {
            process_node (*i);
            auto & values (module.already_generated [*i]);
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
        module.already_generated [array_a].push_back (new (GC) mu::llvmc::skeleton::constant_array (array_a->region, module.module->global, array_type, initializer));
    }
}

void mu::llvmc::analyzer_node::process_array_type (mu::llvmc::ast::array_type * type_a)
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
                module.already_generated [type_a].push_back (new (GC) mu::llvmc::skeleton::array_type (element, number_l->value));
            }
        }
        else
        {
            error = new (GC) mu::core::error_string (U"Expecting number", mu::core::error_type::expecting_a_number, type_a->size->region);
        }
    }
}

void mu::llvmc::analyzer_node::process_asm (mu::llvmc::ast::definite_expression * asm_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (module.module->global);
	size_t predicate_offset (~0);
    process_call_values (asm_a->arguments, asm_a->predicate_position, arguments, most_specific_branch, predicate_offset);
    assert (dynamic_cast <mu::llvmc::skeleton::asm_c *> (arguments [0]) != nullptr);
    auto instruction (new (GC) mu::llvmc::skeleton::inline_asm (asm_a->region, most_specific_branch, arguments, predicate_offset));
    module.already_generated [asm_a].push_back (instruction);
}

void mu::llvmc::analyzer_node::process_loop (mu::llvmc::ast::loop * loop_a)
{
	auto loop_s (new (GC) mu::llvmc::skeleton::loop);
	mu::llvmc::skeleton::branch * loop_branch (module.module->global);
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
				auto argument (dynamic_cast<mu::llvmc::skeleton::value *> (*k));
				if (argument != nullptr)
				{
					auto new_parameter (new (GC) mu::llvmc::skeleton::loop_parameter (loop_a->region, loop_entry_branch, static_cast<mu::llvmc::skeleton::value *> (*k)->type ()));
					loop_s->parameters.push_back (new_parameter);
					module.already_generated [*i].push_back (new_parameter);
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Loop argument must be a value", mu::core::error_type::loop_argument_must_be_value);
				}
			}
			auto branch (new (GC) mu::llvmc::skeleton::branch (loop_branch));
			auto empty (true);
            auto feedback_branch (true);
			mu::llvmc::branch_analyzer branches (module.module->global, error);
			loop_a->for_each_results (
				[&]
				(mu::llvmc::ast::expression * expression_a, size_t index_a)
				{
					process_node (expression_a);
                    if (error == nullptr)
                    {
                        assert (module.already_generated.find (expression_a) != module.already_generated.end ());
                        for (auto i : module.already_generated [expression_a])
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
                    auto element (new (GC) mu::llvmc::skeleton::loop_element_value (expression_a->region, branch, loop_s, index_a));
                    loop_s->elements.push_back (element);
					empty = false;
				},
				[&]
				(mu::llvmc::ast::expression * expression_a, size_t)
				{
					process_node (expression_a);
                    if (error == nullptr)
                    {
                        assert (module.already_generated.find (expression_a) != module.already_generated.end ());
                        for (auto i : module.already_generated [expression_a])
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
                        auto element (new (GC) mu::llvmc::skeleton::loop_element_unit (node_a->region, branch, loop_s, index_a));
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
			switch (loop_s->elements.size ())
			{
				case 0:
				{
					module.already_generated [loop_a].push_back (new (GC) mu::llvmc::skeleton::loop_element_unit (loop_a->region, branch, loop_s, 0));
					break;
				}
				case 1:
				{
					module.already_generated [loop_a].push_back (loop_s->elements [0]);
					break;
				}
				default:
				{
					auto & target (module.already_generated [loop_a]);
					target.insert (target.end (), loop_s->elements.begin (), loop_s->elements.end ());
				}
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Number of arguments does not match number of parameters", mu::core::error_type::mismatch_number_of_arguments_number_of_parameters);
		}
	}
}

mu::llvmc::skeleton::number::number (uint64_t value_a) :
value (value_a)
{
}

mu::llvmc::skeleton::number * mu::llvmc::analyzer_node::process_number (mu::llvmc::ast::number * number_a)
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
			error = new (GC) mu::core::error_string (U"Unable to convert string to number", mu::core::error_type::error_converting_string_to_number);
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Unable to convert string to number", mu::core::error_type::error_converting_string_to_number);		
	}
	return result;
}

void mu::llvmc::analyzer_node::process_constant_int (mu::llvmc::ast::constant_int * constant_a)
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
					module.already_generated [constant_a].push_back (new (GC) mu::llvmc::skeleton::constant_integer (constant_a->region, module.module->global, bits, number_l->value));
				}
			}
			else
			{
				error = new (GC) mu::core::error_string (U"Expecting a number", mu::core::error_type::expecting_a_number);
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Bit width too wide", mu::core::error_type::bit_width_too_wide);
		}
	}
	catch (boost::bad_lexical_cast)
	{
		error = new (GC) mu::core::error_string (U"Unable to convert number to unsigned integer", mu::core::error_type::unable_to_convert_number_to_unsigned_integer);
	}
}

void mu::llvmc::analyzer_node::process_element (mu::llvmc::ast::element * element_a)
{
	process_node (element_a->node);
	if (error == nullptr)
	{
        auto existing (module.already_generated.find (element_a->node));
        if (existing->second.size () > element_a->index)
        {
            auto node (existing->second [element_a->index]);
            auto value (dynamic_cast <mu::llvmc::skeleton::value *> (node));
            if (value != nullptr)
            {
                module.already_generated [element_a].push_back (new (GC) mu::llvmc::skeleton::named (element_a->region, value, element_a->name));
            }
            else
            {
                module.already_generated [element_a].push_back (node);
            }
        }
        else
        {
            error = new (GC) mu::core::error_string (U"No value at index", mu::core::error_type::no_value_at_index, element_a->region);
        }
	}
}

void mu::llvmc::analyzer_node::process_single_node (mu::llvmc::ast::node * node_a)
{
	assert (node_a != nullptr);
	process_node (node_a);
    auto size (module.already_generated [node_a].size ());
	if (error == nullptr && size != 1)
	{
		error = new (GC) mu::core::error_string (U"Expecting 1 value", mu::core::error_type::expecting_one_value);
	}
}

mu::llvmc::skeleton::value * mu::llvmc::analyzer_node::process_value (mu::llvmc::ast::node * node_a)
{
	assert (node_a != nullptr);
	mu::llvmc::skeleton::value * result (nullptr);
	process_single_node (node_a);
	if (error == nullptr)
	{
        auto & nodes (module.already_generated [node_a]);
        assert (nodes.size () == 1);
		result = dynamic_cast <mu::llvmc::skeleton::value *> (nodes [0]);
		if (result == nullptr)
		{
			error = new (GC) mu::core::error_string (U"Node is not value", mu::core::error_type::node_is_not_a_value);
		}
	}
	return result;
}

mu::llvmc::skeleton::type * mu::llvmc::analyzer_node::process_type (mu::llvmc::ast::node * node_a)
{
	mu::llvmc::skeleton::type * result (nullptr);
	process_single_node (node_a);
	if (error == nullptr)
	{
		auto & nodes (module.already_generated [node_a]);
        assert (nodes.size () == 1);
		result = dynamic_cast<mu::llvmc::skeleton::type *> (nodes [0]);
	}
	return result;
}

void mu::llvmc::analyzer_node::process_pointer_type (mu::llvmc::ast::pointer_type * type_a)
{
	auto pointed_type (process_type (type_a->pointed_type));
	if (pointed_type != nullptr)
	{
		module.already_generated [type_a].push_back (new (GC) mu::llvmc::skeleton::pointer_type (pointed_type));
	}
}

void mu::llvmc::analyzer_node::process_integer_type (mu::llvmc::ast::integer_type * type_a)
{
	try
	{
		std::string data_l (type_a->bits.begin (), type_a->bits.end ());
		unsigned int bits (boost::lexical_cast <unsigned int> (data_l));
		if (bits <= 1024)
		{
			module.already_generated [type_a].push_back (new (GC) mu::llvmc::skeleton::integer_type (bits));
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Bit width too wide", mu::core::error_type::bit_width_too_wide);
		}
	}
	catch (boost::bad_lexical_cast)
	{
		error = new (GC) mu::core::error_string (U"Unable to convert number to unsigned integer", mu::core::error_type::unable_to_convert_number_to_unsigned_integer);
	}
}

void mu::llvmc::analyzer_function::process_results (mu::llvmc::analyzer_node & nodes, mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s)
{
	mu::llvmc::branch_analyzer branches (module.module->global, result_m.error);
	function_a->for_each_results (
        [&]
        (mu::llvmc::ast::result * result_a, size_t index_a)
        {
			if (result_a != nullptr)
			{
				auto type (nodes.process_type (result_a->written_type));
				if (type != nullptr)
				{
					auto value (nodes.process_value (result_a->value));
					if (value != nullptr)
					{
                        if (*type == *value->type ())
                        {
                            function_s->results.push_back (new (GC) mu::llvmc::skeleton::result (type, value));
                            branches.add_branch (value->branch, result_a->region);
                        }
                        else
                        {
                            result_m.error = new (GC) mu::core::error_string (U"Actual result type does not match formal result type", mu::core::error_type::actual_formal_result_type_mismatch, result_a->region);
                        }
					}
				}
				else
				{
					result_m.error = new (GC) mu::core::error_string (U"Expecting a type", mu::core::error_type::expecting_a_type);
				}
			}
			else
			{
				result_m.error = new (GC) mu::core::error_string (U"Expecting a result", mu::core::error_type::expecting_a_result);
			}
        },
        [&]
        (mu::llvmc::ast::node * node_a, size_t)
        {
            nodes.process_node (node_a);
            if (result_m.error == nullptr)
            {
                for (auto i : module.already_generated [node_a])
                {
                    auto value (dynamic_cast <mu::llvmc::skeleton::value *> (i));
                    if (value != nullptr)
                    {
                        function_s->results.push_back (i);
                        branches.add_branch (static_cast <mu::llvmc::skeleton::value *> (i)->branch, node_a->region);
                    }
                    else
                    {
                        result_m.error = new (GC) mu::core::error_string (U"Predicate is not a value", mu::core::error_type::expecting_a_value);
                    }
                }
            }
        },
        [&]
        (mu::llvmc::ast::node *, size_t)
        {
            function_s->predicate_offsets.push_back (function_s->results.size ());
        },
        [&]
        (mu::llvmc::ast::node *, size_t)
        {
			branches.new_set ();
            function_s->branch_ends.push_back (function_s->results.size ());
        },
        [&]
        ()
        {
            return result_m.error == nullptr;
        }
	);
}

mu::llvmc::function_result mu::llvmc::analyzer_function::analyze (mu::llvmc::ast::node * function_a)
{
    auto function_l (dynamic_cast<mu::llvmc::ast::function *> (function_a));
    if (function_l != nullptr)
    {
        assert (function_l->branch_ends.size () == function_l->predicate_offsets.size ());
        auto function_s (new (GC) mu::llvmc::skeleton::function (function_a->region, module.module->global));
        result_m.function = function_s;
        module.already_generated [function_a].push_back (function_s);
        mu::llvmc::analyzer_node nodes (module, result_m.error, function_s->entry);
        process_parameters (nodes, function_l, function_s);
        process_results (nodes, function_l, function_s);
        if (result_m.error != nullptr)
        {
            result_m.function = nullptr;
        }
    }
    else
    {
        result_m.error = new (GC) mu::core::error_string (U"Expecting a function", mu::core::error_type::expecting_a_function);
    }
	return result_m;
}

mu::llvmc::module_result mu::llvmc::analyzer_module::analyze (mu::llvmc::ast::node * module_a)
{
	auto module_l (dynamic_cast<mu::llvmc::ast::module *> (module_a));
	if (module_l != nullptr)
	{
        auto module_s (new (GC) mu::llvmc::skeleton::module);
        module = module_s;
		for (auto i (module_l->globals.begin ()), j (module_l->globals.end ()); i != j && result_m.error == nullptr; ++i)
		{
			auto existing (already_generated.find (i->second));
			if (existing == already_generated.end ())
			{
                mu::llvmc::analyzer_node nodes (*this, result_m.error, module_s->global);
                nodes.process_node (i->second);
			}
            if (result_m.error == nullptr)
            {
                assert (module->functions.find (i->first) == module->functions.end ());
                assert (already_generated.find (i->second) != already_generated.end ());
				auto & values (already_generated [i->second]);
				for (auto k (values.begin ()), l (values.end ()); k != l && result_m.error == nullptr; ++k)
				{
					auto function (dynamic_cast <mu::llvmc::skeleton::function *> (*k));
					if (function != nullptr)
					{
						module->functions [i->first] = function;
					}
					else
					{
						result_m.error = new (GC) mu::core::error_string (U"Expecting global", mu::core::error_type::expecting_a_function);
					}
				}
            }
		}
        if (result_m.error == nullptr)
        {
            result_m.module = module_s;
        }
	}
	else
	{
		result_m.error = new (GC) mu::core::error_string (U"Expecting a module", mu::core::error_type::expecting_a_module);
	}
	return result_m;
}

void mu::llvmc::analyzer_node::process_definite_expression (mu::llvmc::ast::definite_expression * expression_a)
{
	auto existing (module.current_expression_generation.find (expression_a));
	if (existing == module.current_expression_generation.end ())
	{
		module.current_expression_generation.insert (expression_a);
		if (!expression_a->arguments.empty ())
		{
			process_node (expression_a->arguments [0]);
			if (error == nullptr)
			{
				mu::llvmc::skeleton::node * target;
                auto & generated = module.already_generated [expression_a->arguments [0]];
                if (!generated.empty ())
                {
                    target = generated [0];
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Expecting target", mu::core::error_type::expecting_a_target);
                }
				if (error == nullptr)
				{
					auto value (dynamic_cast<mu::llvmc::skeleton::value *> (target));
					if (value != nullptr)
					{
						process_value_call (expression_a);
					}
					else
					{
						auto marker (dynamic_cast<mu::llvmc::skeleton::marker *> (target));
						if (marker != nullptr)
						{
							process_marker (expression_a);
						}
						else
						{
							auto join (dynamic_cast<mu::llvmc::skeleton::join *> (target));
							if (join != nullptr)
							{
								process_join (expression_a);
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
                                        error = new (GC) mu::core::error_string (U"Expecting first argument to be call target", mu::core::error_type::expecting_first_argument_to_be_call_target);
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
			error = new (GC) mu::core::error_string (U"Expecting a call target", mu::core::error_type::expecting_a_call_target);
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Cycle in expressions", mu::core::error_type::cycle_in_expressions);
	}
	module.current_expression_generation.erase (expression_a);
	assert (module.current_expression_generation.find (expression_a) == module.current_expression_generation.end ());
	assert (error != nullptr || (module.already_generated.find (expression_a) != module.already_generated.end ()));
}

void mu::llvmc::analyzer_node::process_identity (mu::llvmc::ast::definite_expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (module.module->global);
	size_t predicate_offset (~0);
	process_call_values (expression_a->arguments, expression_a->predicate_position, arguments, most_specific_branch, predicate_offset);
    bool result;
    auto source (new (GC) mu::llvmc::skeleton::identity_call (arguments, predicate_offset));
    switch (predicate_offset)
    {
        case 0:
            assert (false);
            break;
        case 1:
        {
            result = false;
            auto element (new (GC) mu::llvmc::skeleton::identity_element_unit (most_specific_branch, source));
            source->elements.push_back (element);
            module.already_generated [expression_a].push_back (element);
            break;
        }
        case 2:
        {
            result = false;
            auto element (new (GC) mu::llvmc::skeleton::identity_element_value (most_specific_branch, source, 1));
            source->elements.push_back (element);
            module.already_generated [expression_a].push_back (element);
            break;
        }
        default:
        {
            auto & values (module.already_generated [expression_a]);
            for (size_t i (1); i < predicate_offset; ++i)
            {
                auto element (new (GC) mu::llvmc::skeleton::identity_element_value (most_specific_branch, source, i));
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
        auto & results (module.already_generated [expression_a]);
        results.insert (results.end (), arguments.begin () + 1, arguments.begin () + predicate_offset);
    }
}

void mu::llvmc::analyzer_node::process_value_call (mu::llvmc::ast::definite_expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (entry);
	size_t predicate_offset (~0);
	process_call_values (expression_a->arguments, expression_a->predicate_position, arguments, most_specific_branch, predicate_offset);
	auto result (false);
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
					error = new (GC) mu::core::error_string (U"Argument to function is not a value", mu::core::error_type::argument_to_function_is_not_a_value);
				}
			}
			if (error == nullptr)
			{
				if ((i == j) == (k == l))
				{
					if (!arguments.empty ())
					{
						auto call (new (GC) mu::llvmc::skeleton::function_call (function_type->function, most_specific_branch, arguments, predicate_offset));
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
							(mu::llvmc::skeleton::node * node_a, size_t index_a)
							{
                                auto element (new (GC) mu::llvmc::skeleton::call_element_value (expression_a->region, branch, call, index_a));
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
                                    auto element (new (GC) mu::llvmc::skeleton::call_element_unit (expression_a->region, branch, call));
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
                        switch (returned_results.size ())
                        {
                            case 0:
                            {
                                auto element (new (GC) mu::llvmc::skeleton::call_element_unit (expression_a->region, most_specific_branch, call));
                                module.already_generated [expression_a].push_back (element);
                                call->elements.push_back (element);
                                break;
                            }
                            case 1:
                            {
                                module.already_generated [expression_a].push_back (returned_results [0]);
                                break;
                            }
                            default:
                            {
                                result = true;
                                auto & target (module.already_generated [expression_a]);
                                target.insert (target.end (), returned_results.begin (), returned_results.end ());
                                break;
                            }
                        }
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Incorrect number of arguments", mu::core::error_type::incorrect_number_of_arguments);
				}
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Pointer does not point to a function", mu::core::error_type::pointer_does_not_point_to_a_function);
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Only function pointers can be the target of a call", mu::core::error_type::only_function_pointers_can_be_target_of_call);
	}
	module.current_expression_generation.erase (expression_a);
}

void mu::llvmc::analyzer_node::process_join (mu::llvmc::ast::definite_expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::value *> arguments;
	for (auto i (expression_a->arguments.begin () + 1), j (expression_a->arguments.end ()); i != j && error == nullptr; ++i)
	{
		process_node (*i);
		if (error == nullptr)
		{
            auto & values (module.already_generated [*i]);
            for (auto k (values.begin ()), l (values.end ()); k != l; ++k)
            {
                auto value (dynamic_cast<mu::llvmc::skeleton::value *> (*k));
                if (value != nullptr)
                {
                    arguments.push_back (value);
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Join arguments must be values", mu::core::error_type::join_arguments_must_be_values);
                }
            }
		}
	}
	mu::set <mu::llvmc::skeleton::branch *> marked_branches;
	mu::set <mu::llvmc::skeleton::branch *> joined_branches;
	for (auto i (arguments.begin ()), j (arguments.end ()); i != j && error == nullptr; ++i)
	{
		auto value (*i);
		auto existing_marked (marked_branches.find (value->branch));
		if (existing_marked == marked_branches.end ())
		{
			for (auto k (value->branch); k != nullptr && error == nullptr; k = k->parent)
			{
				auto existing_joined (joined_branches.find (k));
				if (existing_joined == joined_branches.end ())
				{
					marked_branches.insert (k);
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Branches are not distinct", mu::core::error_type::branches_are_not_disjoint);
				}
			}
			joined_branches.insert (value->branch);
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Branches are not disjoint", mu::core::error_type::branches_are_not_disjoint);
		}
	}
	if (error == nullptr)
	{
		if (arguments.size () > 1)
		{
			auto least_specific_branch (arguments [0]->branch);
			auto type (arguments [0]->type ());
			for (auto i (arguments.begin () + 1), j (arguments.end ()); i != j; ++i)
			{
				least_specific_branch = least_specific_branch->least_specific ((*i)->branch);
				auto other_type ((*i)->type ());
				if (*type != *other_type)
				{
					error = new (GC) mu::core::error_string (U"Joining types are different", mu::core::error_type::joining_types_are_different);
				}
			}
			if (error == nullptr)
			{
				auto parent (least_specific_branch->parent);
				assert (parent != module.module->global);
				module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::join_value (expression_a->region, parent, arguments));
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Must be joining at least two values", mu::core::error_type::must_be_joining_at_least_two_values);
		}
	}
}

void mu::llvmc::analyzer_node::process_call_values (mu::vector <mu::llvmc::ast::node *> const & arguments, size_t predicate_offset, mu::vector <mu::llvmc::skeleton::node *> & arguments_a, mu::llvmc::skeleton::branch * & most_specific_branch, size_t & predicate_position_a)
{
    mu::llvmc::branch_analyzer branches (most_specific_branch, error);
	size_t predicate_position_l (~0);
	mu::llvmc::ast::for_each_argument (
		arguments,
		predicate_offset,
		[&]
		(mu::llvmc::ast::node * node_a, size_t index)
		{
			process_node (node_a);
			if (error == nullptr)
			{
                auto & nodes (module.already_generated [node_a]);
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
			process_node (node_a);
			if (error == nullptr)
			{
                auto & nodes (module.already_generated [node_a]);
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

void mu::llvmc::analyzer_node::process_binary_integer_instruction (mu::llvmc::ast::definite_expression * expression_a, size_t predicate_offset, mu::vector <mu::llvmc::skeleton::node *> const & arguments, mu::llvmc::skeleton::branch * most_specific_branch)
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
							module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
						}
						else
						{
							error = new (GC) mu::core::error_string (U"Instruction left and right arguments must be same width", mu::core::error_type::instruction_arguments_must_have_same_bit_width);
						}
					}
					else
					{
						error = new (GC) mu::core::error_string (U"Instruction right argument must be an integer type", mu::core::error_type::instruction_arguments_must_be_integers);
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Instruction left argument must be an integer type", mu::core::error_type::instruction_arguments_must_be_integers);
				}
			}
			else
			{
				error = new (GC) mu::core::error_string (U"Instruction right argument must be a value", mu::core::error_type::instruction_arguments_must_be_values);
			}
		}
		else
		{
			error = new (GC) mu::core::error_string (U"Instruction left argument must be a value", mu::core::error_type::instruction_arguments_must_be_values);
		}
	}
	else
	{
		error = new (GC) mu::core::error_string (U"Instruction instruction expects two arguments", mu::core::error_type::instruction_expects_two_arguments);
	}
}

void mu::llvmc::analyzer_node::process_marker (mu::llvmc::ast::definite_expression * expression_a)
{
	mu::vector <mu::llvmc::skeleton::node *> arguments;
	mu::llvmc::skeleton::branch * most_specific_branch (module.module->global);
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
                        module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Alloca instruction expects its argument to be a type", mu::core::error_type::alloca_argument_type);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Alloca instruction expects one argument", mu::core::error_type::alloca_expects_one_argument);
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
                                error = new (GC) mu::core::error_string (U"Inline asm requires value arguments", mu::core::error_type::inline_asm_requires_values);
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
                                    module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Second argument to bitcast must be a pointer type", mu::core::error_type::argument_must_be_pointer_type);
                                }
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"First argument to bitcast must be a pointer type", mu::core::error_type::argument_must_be_pointer_type);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Second argument to bitcast must be a type", mu::core::error_type::expecting_a_type);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"First argument to bitcast must be a value", mu::core::error_type::instruction_arguments_must_be_values);
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
                                            module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                                        }
                                        else
                                        {
                                            error = new (GC) mu::core::error_string (U"Cmpxchg requires argument one to point to type of argument three", mu::core::error_type::cmpxchg_one_point_three);
                                        }
                                    }
                                    else									
                                    {
                                        error = new (GC) mu::core::error_string (U"Cmpxchg requires argument one to point to type of argument two", mu::core::error_type::cmpxchg_one_point_two);
                                    }
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Cmpxchg requires argument one to be a pointer", mu::core::error_type::cmpxchg_argument_one_pointer);
                                }
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"Cmpxchg requires arguments to be values", mu::core::error_type::instruction_arguments_must_be_values);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Cmpxchg requires arguments to be values", mu::core::error_type::instruction_arguments_must_be_values);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Cmpxchg requires arguments to be values", mu::core::error_type::instruction_arguments_must_be_values);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Cmpxchg requires three arguments", mu::core::error_type::cmpxchg_requires_three_arguments);
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
											assert (dynamic_cast <mu::llvmc::skeleton::integer_type *> (index->type ()));
											if (static_cast <mu::llvmc::skeleton::integer_type *> (index->type ())->bits != 32)
											{
												error = new (GC) mu::core::error_string (U"Getelementptr requires trailing index types to be 32bit integers", mu::core::error_type::getelementptr_trailing_32bit);
											}
										}
										else
										{
											error = new (GC) mu::core::error_string (U"Getelementptr requires trailing indicies to be constant integers", mu::core::error_type::getelementptr_trailing_constant);
										}
									}
									if (error == nullptr)
									{
										module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
									}
								}
								else
								{
									error = new (GC) mu::core::error_string (U"Getelementptr requires pointer index to be an integer", mu::core::error_type::getelementptr_first_argument_integer_type);
								}
							}
							else
							{
								error = new (GC) mu::core::error_string (U"Getelementptr first argument must be a pointer", mu::core::error_type::getelementptr_requires_pointer_type);
							}
						}
						else
						{
							error = new (GC) mu::core::error_string (U"Getelementptr requires its arguments to be values", mu::core::error_type::getelementptr_requires_values);							
						}
					}
					else
					{
						error = new (GC) mu::core::error_string (U"Getelementptr requires its arguments to be values", mu::core::error_type::getelementptr_requires_values);
					}
				}
				else
				{
					error = new (GC) mu::core::error_string (U"Getelementptr requires at least two arguments", mu::core::error_type::getelementptr_requires_two);
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
                                        module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                                    }
                                    else
                                    {
                                        error = new (GC) mu::core::error_string (U"ICMP arguments must be the same type", mu::core::error_type::icmp_arguments_same_type);
                                    }
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"ICMP arguments must be integers", mu::core::error_type::icmp_arguments_integers);
                                }
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"ICMP right argument must be a value", mu::core::error_type::icmp_right_argument_value);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"ICMP left argument must be a value", mu::core::error_type::icmp_left_argument_value);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"ICMP first argument must be predicate", mu::core::error_type::icmp_first_argument_predicate);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"ICMP instruction expects a predicate and two arguments", mu::core::error_type::icmp_expects_predicate_two_arguments);
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
                                auto false_const (new (GC) mu::llvmc::skeleton::constant_integer (expression_a->region, module.module->global, 1, 0));
                                auto true_const (new (GC) mu::llvmc::skeleton::constant_integer (expression_a->region, module.module->global, 1, 1));
                                arguments.push_back (false_const);
                                arguments.push_back (true_const);
                                auto switch_i (new (GC) mu::llvmc::skeleton::switch_i (most_specific_branch, arguments));
                                auto true_branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
                                auto false_branch (new (GC) mu::llvmc::skeleton::branch (most_specific_branch));
                                auto true_element (new (GC) mu::llvmc::skeleton::switch_element (expression_a->region, true_branch, switch_i, true_const));
                                auto false_element (new (GC) mu::llvmc::skeleton::switch_element (expression_a->region, false_branch, switch_i, false_const));
                                auto & values (module.already_generated [expression_a]);
                                values.push_back (true_element);
                                values.push_back (false_element);
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"If instruction expects 1 bit integer", mu::core::error_type::if_instruction_expects_one_bit_integer);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"If instruction expects an integer type value", mu::core::error_type::if_instruction_expects_integer_type_value);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"If instruction expects a value argument", mu::core::error_type::if_instruction_expects_a_value_argument);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"If instruction expects one argument", mu::core::error_type::if_instruction_expects_one_argument);
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
                                module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"Ptrfromint instruction requires second argument to be a pointer type", mu::core::error_type::expecting_integer_type);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Ptrfromint source must be an integer", mu::core::error_type::expecting_integer_type);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Ptrfromint instruction requires first argument to be value", mu::core::error_type::expecting_a_value);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Ptrfromint instruction requires two arguments", mu::core::error_type::ptr_to_int_expects_two);
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
                            module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Load argument must be a pointer type", mu::core::error_type::load_argument_pointer_type);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Load argument must be a value", mu::core::error_type::load_argument_must_be_values);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Load instruction expects two arguments", mu::core::error_type::load_expects_one_argument);
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
                                module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"Ptrtoint instruction requires second argument to be an integer type", mu::core::error_type::expecting_integer_type);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Ptrtoint source must be a pointer", mu::core::error_type::expecting_pointer_type);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Ptrtoint instruction requires first argument to be value", mu::core::error_type::expecting_a_value);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Ptrtoint instruction requires two arguments", mu::core::error_type::ptr_to_int_expects_two);
                }
                break;
            }
            case mu::llvmc::instruction_type::sdiv:
            {
                process_binary_integer_instruction (expression_a, predicate_offset, arguments, most_specific_branch);
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
                                    module.already_generated [expression_a].push_back (new (GC) mu::llvmc::skeleton::instruction (expression_a->region, most_specific_branch, arguments, predicate_offset));
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Type pointed to by store right argument does not match type of left argument", mu::core::error_type::store_right_pointed_type_doesnt_match_left);
                                }
                            }
                            else
                            {
                                error = new (GC) mu::core::error_string (U"Store right argument must be a pointer type", mu::core::error_type::store_right_argument_pointer_type);
                            }
                        }
                        else
                        {
                            error = new (GC) mu::core::error_string (U"Store right argument must be a value", mu::core::error_type::store_arguments_must_be_values);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Store left argument must be a value", mu::core::error_type::store_arguments_must_be_values);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Store instruction expects two arguments", mu::core::error_type::store_expects_two_arguments);
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
                                        error = new (GC) mu::core::error_string (U"Switch requires case arguments to be same type as input", mu::core::error_type::switch_requires_matching_case_types);
                                    }
                                    auto existing (used.find (constant->value_m));
                                    if (existing != used.end ())
                                    {
                                        error = new (GC) mu::core::error_string (U"Switch requires case arguments to be unique", mu::core::error_type::switch_requires_unique_case);
                                    }
                                    used.insert (constant->value_m);
                                }
                                else
                                {
                                    error = new (GC) mu::core::error_string (U"Switch requires case arguments to be constant integers", mu::core::error_type::switch_requires_case_constant);
                                }
                            }
                            if (error == nullptr)
                            {
                                result = true;
                                auto & values (module.already_generated [expression_a]);
                                auto switch_i (new (GC) mu::llvmc::skeleton::switch_i (most_specific_branch, arguments));
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
                            error = new (GC) mu::core::error_string (U"Switch requires input to be an integer", mu::core::error_type::switch_requires_integer);
                        }
                    }
                    else
                    {
                        error = new (GC) mu::core::error_string (U"Switch requires input to be a value", mu::core::error_type::switch_requires_value);
                    }
                }
                else
                {
                    error = new (GC) mu::core::error_string (U"Switch requires an input argument", mu::core::error_type::switch_requires_input);
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
	assert (error != nullptr || (module.already_generated.find (expression_a) != module.already_generated.end ()));
}

mu::llvmc::analyzer_node::analyzer_node (mu::llvmc::analyzer_module & module_a, mu::core::error * & error_a, mu::llvmc::skeleton::branch * entry_a) :
module (module_a),
error (error_a),
entry (entry_a)
{
}