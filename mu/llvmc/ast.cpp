#include <mu/llvmc/ast.hpp>

#include <gc_cpp.h>

#include <mu/core/error_string.hpp>
#include <mu/llvmc/parser.hpp>

mu::llvmc::ast::module::module (mu::llvmc::template_context * template_a) :
node (template_a)
{
}

mu::llvmc::ast::node::node (mu::llvmc::template_context * template_a) :
template_m (template_a),
assigned (false)
{
}

mu::llvmc::ast::node::~node ()
{
}

mu::llvmc::ast::value::value (mu::llvmc::skeleton::node * node_a, mu::llvmc::template_context * template_a):
node (template_a),
node_m (node_a)
{
}

mu::llvmc::ast::element::element (mu::llvmc::ast::node * node_a, size_t index_a, size_t total_a, mu::string const & name_a, mu::core::region const & region_a, mu::llvmc::template_context * template_a) :
node (template_a),
node_m (node_a),
index (index_a),
total (total_a),
name (name_a)
{
    region = region_a;
}

mu::llvmc::ast::parameter::parameter (mu::llvmc::template_context * template_a) :
node (template_a)
{
}

mu::llvmc::ast::parameter::parameter (mu::string const & name_a, mu::llvmc::ast::node * type_a, mu::llvmc::template_context * template_a) :
node (template_a),
type (type_a),
name (name_a)
{
}

mu::llvmc::ast::expression::expression (std::initializer_list <mu::llvmc::ast::node *> arguments_a, std::initializer_list <mu::llvmc::ast::node *> predicates_a, mu::llvmc::template_context * template_a) :
node (template_a),
predicate_position (arguments_a.size ())
{
    arguments.insert (arguments.end (), arguments_a.begin (), arguments_a.end ());
    arguments.insert (arguments.end (), predicates_a.begin (), predicates_a.end ());
}

mu::llvmc::ast::result::result (mu::llvmc::ast::node * written_type_a, mu::llvmc::ast::node * value_a, mu::llvmc::template_context * template_a):
node (template_a),
written_type (written_type_a),
value (value_a)
{
}

void mu::llvmc::ast::expression::set_predicate_position ()
{
    assert (predicate_position == ~0);
    predicate_position = arguments.size ();
}

mu::llvmc::ast::integer_type::integer_type (mu::string const & bits_a, mu::llvmc::template_context * template_a) :
node (template_a),
bits (bits_a)
{
}

mu::llvmc::ast::pointer_type::pointer_type (mu::llvmc::ast::node * pointed_type_a, mu::llvmc::template_context * template_a) :
node (template_a),
pointed_type (pointed_type_a)
{
}

mu::llvmc::ast::constant_int::constant_int (mu::string const & bits_a, mu::llvmc::ast::node * number_a, mu::llvmc::template_context * template_a) :
node (template_a),
bits (bits_a),
number (number_a)
{
}

mu::llvmc::ast::expression::expression (mu::llvmc::template_context * template_a) :
node (template_a),
predicate_position (~0)
{
}

mu::llvmc::ast::result::result (mu::llvmc::template_context * template_a) :
node (template_a)
{
}

void mu::llvmc::ast::loop::set_argument_offset ()
{
    assert (argument_predicate_offset == ~0);
    argument_predicate_offset = arguments.size ();
}

void mu::llvmc::ast::loop::add_predicate_offset ()
{
    predicate_offsets.push_back (results.size ());
}

void mu::llvmc::ast::loop::add_branch_end ()
{
    branch_ends.push_back (results.size ());
}

mu::llvmc::ast::loop::loop (mu::llvmc::template_context * template_a) :
node (template_a),
argument_predicate_offset (~0)
{
}

mu::llvmc::ast::asm_c::asm_c (mu::llvmc::ast::node * type_a, mu::string const & text_a, mu::string const & constraints_a, mu::llvmc::template_context * template_a) :
node (template_a),
type (type_a),
text (text_a),
constraints (constraints_a)
{
}

mu::llvmc::ast::array_type::array_type (mu::llvmc::ast::node * element_type_a, mu::llvmc::ast::node * size_a, mu::llvmc::template_context * template_a) :
node (template_a),
element_type (element_type_a),
size (size_a)
{
}

mu::llvmc::ast::global_variable::global_variable (mu::llvmc::ast::node * initializer_a, mu::llvmc::template_context * template_a) :
node (template_a),
initializer (initializer_a)
{
}

mu::llvmc::ast::join_branch & mu::llvmc::ast::join::add_branch ()
{
    branches.push_back (decltype (branches)::value_type ());
    auto & result (branches [branches.size () - 1]);
    return result;
}

void mu::llvmc::ast::visitor::unexpected (mu::llvmc::ast::node * node_a)
{
    assert (false);
}

void mu::llvmc::ast::visitor::node (mu::llvmc::ast::node * node_a)
{
    unexpected (node_a);
}

void mu::llvmc::ast::visitor::array_type (mu::llvmc::ast::array_type * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::constant_int (mu::llvmc::ast::constant_int * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::integer_type (mu::llvmc::ast::integer_type * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::pointer_type (mu::llvmc::ast::pointer_type * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::constant_array (mu::llvmc::ast::constant_array * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::global_variable (mu::llvmc::ast::global_variable * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::expression (mu::llvmc::ast::expression * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::constant_pointer_null (mu::llvmc::ast::constant_pointer_null * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::join (mu::llvmc::ast::join * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::loop (mu::llvmc::ast::loop * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::unit (mu::llvmc::ast::unit * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::asm_c (mu::llvmc::ast::asm_c * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::value (mu::llvmc::ast::value * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::module (mu::llvmc::ast::module * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::number (mu::llvmc::ast::number * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::result (mu::llvmc::ast::result * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::element (mu::llvmc::ast::element * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::function (mu::llvmc::ast::function * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::unit_type (mu::llvmc::ast::unit_type * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::loop_parameter (mu::llvmc::ast::loop_parameter * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::parameter (mu::llvmc::ast::parameter * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::struct_type (mu::llvmc::ast::struct_type * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::undefined (mu::llvmc::ast::undefined * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::node::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->node (this);
}

void mu::llvmc::ast::array_type::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->array_type (this);
}

void mu::llvmc::ast::constant_int::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->constant_int (this);
}

void mu::llvmc::ast::integer_type::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->integer_type (this);
}

void mu::llvmc::ast::pointer_type::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->pointer_type (this);
}

void mu::llvmc::ast::constant_array::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->constant_array (this);
}

void mu::llvmc::ast::global_variable::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->global_variable (this);
}

void mu::llvmc::ast::expression::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->expression (this);
}

void mu::llvmc::ast::constant_pointer_null::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->constant_pointer_null (this);
}

void mu::llvmc::ast::join::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->join (this);
}

void mu::llvmc::ast::loop::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->loop (this);
}

void mu::llvmc::ast::unit::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->unit (this);
}

void mu::llvmc::ast::asm_c::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->asm_c (this);
}

void mu::llvmc::ast::value::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->value (this);
}

void mu::llvmc::ast::module::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->module (this);
}

void mu::llvmc::ast::number::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->number (this);
}

void mu::llvmc::ast::result::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->result (this);
}

void mu::llvmc::ast::element::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->element (this);
}

void mu::llvmc::ast::function::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->function (this);
}

void mu::llvmc::ast::unit_type::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->unit_type (this);
}

void mu::llvmc::ast::loop_parameter::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->loop_parameter (this);
}

void mu::llvmc::ast::parameter::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->parameter (this);
}

void mu::llvmc::ast::struct_type::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->struct_type (this);
}

void mu::llvmc::ast::undefined::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->undefined (this);
}

mu::llvmc::ast::loop_parameter::loop_parameter (mu::string const & name_a, mu::llvmc::template_context * template_a) :
node (template_a),
name (name_a)
{
}

mu::llvmc::ast::node * mu::llvmc::ast::loop_parameter::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::loop_parameter (*this));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::module::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::module (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::number::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::number (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::result::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::result (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::function::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::function (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::array_type::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::array_type (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::struct_type::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::struct_type (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::constant_int::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::constant_int (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::integer_type::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::integer_type (*this));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::pointer_type::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::pointer_type (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::constant_array::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::constant_array (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::global_variable::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::global_variable (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::expression::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::expression (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::constant_pointer_null::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::constant_pointer_null (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::join::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::join (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::loop::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::loop (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::unit::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::unit (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::asm_c::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::asm_c (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::value::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::value (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::element::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::element (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::parameter::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::parameter (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::undefined::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::undefined (*this, context_a));
	return result;
}

mu::llvmc::ast::array_type::array_type (mu::llvmc::ast::array_type const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
element_type (other_a.element_type->clone (context_a)),
size (other_a.size->clone (context_a))
{
}

mu::llvmc::ast::struct_type::struct_type (mu::llvmc::ast::struct_type const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m)
{
	for (auto i: other_a.elements)
	{
		elements.push_back (i->clone (context_a));
	}
}

mu::llvmc::ast::constant_int::constant_int (mu::llvmc::ast::constant_int const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
bits (other_a.bits),
number (other_a.number->clone (context_a))
{
}

mu::llvmc::ast::integer_type::integer_type (mu::llvmc::ast::integer_type const & other_a) :
node (other_a.template_m),
bits (other_a.bits)
{
}

mu::llvmc::ast::pointer_type::pointer_type (mu::llvmc::ast::pointer_type const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
pointed_type (other_a.pointed_type->clone (context_a))
{
}

mu::llvmc::ast::constant_array::constant_array (mu::llvmc::ast::constant_array const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
type (other_a.type->clone (context_a))
{
	for (auto i: other_a.initializer)
	{
		initializer.push_back (i->clone (context_a));
	}
}

mu::llvmc::ast::loop_parameter::loop_parameter (mu::llvmc::ast::loop_parameter const & other_a) :
node (other_a.template_m),
name (other_a.name)
{
}

mu::llvmc::ast::global_variable::global_variable (mu::llvmc::ast::global_variable const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
initializer (other_a.initializer->clone (context_a))
{
}

mu::llvmc::ast::expression::expression (mu::llvmc::ast::expression const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
predicate_position (other_a.predicate_position)
{
	for (auto i: other_a.arguments)
	{
		arguments.push_back (i->clone (context_a));
	}
}

mu::llvmc::ast::constant_pointer_null::constant_pointer_null (mu::llvmc::ast::constant_pointer_null const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
type (other_a.type->clone (context_a))
{
}

mu::llvmc::ast::join::join (mu::llvmc::ast::join const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m)
{
	for (auto & i: other_a.branches)
	{
		branches.push_back (mu::llvmc::ast::join_branch ());
		auto & target (branches [branches.size () - 1]);
		for (auto j: i.arguments)
		{
			target.arguments.push_back (j->clone (context_a));
		}
		for (auto j: i.predicates)
		{
			target.predicates.push_back (j->clone (context_a));
		}
	}
}

mu::llvmc::ast::loop::loop (mu::llvmc::ast::loop const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
argument_predicate_offset (other_a.argument_predicate_offset),
predicate_offsets (other_a.predicate_offsets),
branch_ends (other_a.branch_ends)
{
	for (auto i: other_a.arguments)
	{
		arguments.push_back (i->clone (context_a));
	}
	for (auto i: other_a.parameters)
	{
		parameters.push_back (i->clone (context_a));
	}
	for (auto i: other_a.roots)
	{
		roots.push_back (i->clone (context_a));
	}
	for (auto i: other_a.results)
	{
		results.push_back (i->clone (context_a));
	}
}

mu::llvmc::ast::asm_c::asm_c (mu::llvmc::ast::asm_c const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
type (other_a.type->clone (context_a)),
text (other_a.text),
constraints (other_a.constraints)
{
}

mu::llvmc::ast::module::module (mu::llvmc::ast::module const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m)
{
	for (auto & i: other_a.globals)
	{
		globals.push_back (i->clone (context_a));
	}
}

mu::llvmc::ast::result::result (mu::llvmc::ast::result const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
written_type (other_a.written_type->clone (context_a)),
value (other_a.value->clone (context_a))
{
}

mu::llvmc::ast::element::element (mu::llvmc::ast::element const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
node_m (other_a.node_m->clone (context_a)),
index (other_a.index),
total (other_a.total),
name (other_a.name)
{
}

mu::llvmc::ast::function::function (mu::llvmc::ast::function const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
branch_ends (other_a.branch_ends),
predicate_offsets (other_a.predicate_offsets)
{
	for (auto i: other_a.parameters)
	{
		parameters.push_back (i->clone (context_a));
	}
	for (auto i: other_a.results)
	{
		results.push_back (i->clone (context_a));
	}
	for (auto i: other_a.roots)
	{
		roots.push_back (i->clone (context_a));
	}
}

mu::llvmc::ast::parameter::parameter (mu::llvmc::ast::parameter const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
type (other_a.type->clone (context_a)),
name (other_a.name)
{
}

mu::llvmc::ast::undefined::undefined (mu::llvmc::ast::undefined const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
type (other_a.type->clone (context_a))
{
}

mu::llvmc::ast::node * mu::llvmc::ast::node::clone (mu::llvmc::clone_context & context_a)
{
	mu::llvmc::ast::node * result;
	auto existing (context_a.generated.find (this));
	if (existing != context_a.generated.end ())
	{
		result = existing->second;
	}
	else
	{
        assert (context_a.template_m != nullptr);
        if (context_a.template_m->should_clone (template_m))
        {
            result = do_clone (context_a);
            context_a.generated [this] = result;
        }
        else
        {
            result = this;
        }
	}
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::node::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::node (*this, context_a));
	return result;
}

mu::llvmc::ast::node::node (mu::llvmc::ast::node const & other_a, mu::llvmc::clone_context & context_a) :
template_m (other_a.template_m),
region (other_a.region)
{
}

mu::llvmc::ast::unit_type::unit_type (mu::llvmc::ast::unit_type const & other_a) :
node (other_a.template_m)
{
}

mu::llvmc::ast::node * mu::llvmc::ast::unit_type::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::unit_type (*this));
	return result;
}

mu::llvmc::ast::unit_type::unit_type (mu::llvmc::template_context * template_a) :
node (template_a)
{
}

mu::llvmc::ast::template_parameter::template_parameter (mu::string const & name_a, mu::llvmc::template_context * template_a) :
node (template_a),
name (name_a)
{
}

mu::llvmc::ast::template_c::template_c (mu::llvmc::ast::template_c const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m)
{
	for (auto i: other_a.parameters)
	{
		parameters.push_back (i->clone (context_a));
	}
	for (auto i: other_a.body)
	{
		body.push_back (i->clone (context_a));
	}
}

mu::llvmc::ast::template_parameter::template_parameter (mu::llvmc::ast::template_parameter const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
argument (other_a.argument),
name (other_a.name)
{
}

void mu::llvmc::ast::template_parameter::visit (mu::llvmc::ast::visitor * visitor_a)
{
	visitor_a->template_parameter (this);
}

void mu::llvmc::ast::template_c::visit (mu::llvmc::ast::visitor * visitor_a)
{
	visitor_a->template_c (this);
}

void mu::llvmc::ast::visitor::template_c (mu::llvmc::ast::template_c * node_a)
{
	node (node_a);
}

void mu::llvmc::ast::visitor::template_parameter (mu::llvmc::ast::template_parameter * node_a)
{
	node (node_a);
}

mu::llvmc::ast::node * mu::llvmc::ast::template_parameter::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::template_parameter (*this, context_a));
	return result;
}

mu::llvmc::ast::node * mu::llvmc::ast::template_c::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::template_c (*this, context_a));
	return result;
}

mu::llvmc::ast::number::number (mu::llvmc::ast::number const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
number_m (other_a.number_m)
{
}

mu::llvmc::ast::unit::unit (mu::llvmc::ast::unit const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m)
{
}

mu::llvmc::ast::value::value (mu::llvmc::ast::value const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
node_m (other_a.node_m)
{
}

mu::llvmc::ast::entry::entry (mu::llvmc::ast::entry const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m),
function (other_a.function->clone (context_a))
{    
}

mu::llvmc::ast::node * mu::llvmc::ast::entry::do_clone (mu::llvmc::clone_context & context_a)
{
    auto result (new (GC) mu::llvmc::ast::entry (*this, context_a));
    return result;
}

void mu::llvmc::ast::entry::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->entry (this);
}

void mu::llvmc::ast::visitor::entry (mu::llvmc::ast::entry * node_a)
{
    node (node_a);
}

mu::llvmc::ast::set::set (mu::llvmc::ast::set const & other_a, mu::llvmc::clone_context & context_a) :
node (other_a.template_m)
{
	for (auto i: other_a.nodes)
	{
		nodes.push_back (i->clone (context_a));
	}
}

mu::llvmc::ast::node * mu::llvmc::ast::set::do_clone (mu::llvmc::clone_context & context_a)
{
	auto result (new (GC) mu::llvmc::ast::set (*this, context_a));
	return result;
}

void mu::llvmc::ast::set::visit (mu::llvmc::ast::visitor * visitor_a)
{
	visitor_a->set (this);
}

void mu::llvmc::ast::visitor::set (mu::llvmc::ast::set * node_a)
{
	node (node_a);
}

mu::llvmc::ast::array_type::array_type (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::template_c::template_c (mu::llvmc::template_context * base_a, mu::llvmc::template_context * context_a) :
node (context_a),
base (base_a)
{
    assert (base_a != nullptr);
}

mu::llvmc::ast::struct_type::struct_type (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::pointer_type::pointer_type (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::constant_array::constant_array (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::global_variable::global_variable (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::constant_pointer_null::constant_pointer_null (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::set::set (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::join::join (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::unit::unit (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::asm_c::asm_c (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::entry::entry (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::function::function (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::ast::undefined::undefined (mu::llvmc::template_context * context_a) :
node (context_a)
{
}

mu::llvmc::clone_context::clone_context (mu::llvmc::template_context * template_a) :
template_m (template_a)
{
}