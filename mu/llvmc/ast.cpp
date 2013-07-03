#include <mu/llvmc/ast.hpp>

#include <gc_cpp.h>

#include <mu/core/error_string.hpp>

mu::llvmc::ast::module::module ()
{
}

mu::llvmc::ast::node::~node ()
{
}

mu::llvmc::ast::value::value (mu::llvmc::skeleton::node * node_a):
node_m (node_a)
{
}

mu::llvmc::ast::element::element (mu::llvmc::ast::node * node_a, size_t index_a, size_t total_a, mu::string const & name_a, mu::core::region const & region_a):
node (node_a),
index (index_a),
total (total_a),
name (name_a)
{
    region = region_a;
}

mu::llvmc::ast::parameter::parameter (mu::string const & name_a, mu::llvmc::ast::node * type_a):
type (type_a),
name (name_a)
{
}

mu::llvmc::ast::result::result (mu::llvmc::ast::node * written_type_a):
written_type (written_type_a),
value (nullptr)
{
}

mu::llvmc::ast::definite_expression::definite_expression () :
predicate_position (~0)
{
}

void mu::llvmc::ast::definite_expression::set_predicate_position ()
{
    assert (predicate_position == ~0);
    predicate_position = arguments.size ();
}

mu::llvmc::ast::integer_type::integer_type (mu::string const & bits_a) :
bits (bits_a)
{
}

mu::llvmc::ast::pointer_type::pointer_type (mu::llvmc::ast::node * pointed_type_a) :
pointed_type (pointed_type_a)
{
}

mu::llvmc::ast::constant_int::constant_int (mu::string const & bits_a, mu::llvmc::ast::node * number_a) :
bits (bits_a),
number (number_a)
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

mu::llvmc::ast::loop::loop () :
argument_predicate_offset (~0)
{
}

mu::llvmc::ast::asm_c::asm_c (mu::llvmc::ast::node * type_a, mu::string const & text_a, mu::string const & constraints_a) :
type (type_a),
text (text_a),
constraints (constraints_a)
{
}

mu::llvmc::ast::array_type::array_type (mu::llvmc::ast::node * element_type_a, mu::llvmc::ast::node * size_a) :
element_type (element_type_a),
size (size_a)
{
}

mu::llvmc::ast::global_variable::global_variable (mu::llvmc::ast::node * initializer_a) :
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

void mu::llvmc::ast::visitor::set_expression (mu::llvmc::ast::set_expression * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::global_variable (mu::llvmc::ast::global_variable * node_a)
{
    node (node_a);
}

void mu::llvmc::ast::visitor::definite_expression (mu::llvmc::ast::definite_expression * node_a)
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

void mu::llvmc::ast::set_expression::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->set_expression (this);
}

void mu::llvmc::ast::global_variable::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->global_variable (this);
}

void mu::llvmc::ast::definite_expression::visit (mu::llvmc::ast::visitor * visitor_a)
{
    visitor_a->definite_expression (this);
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