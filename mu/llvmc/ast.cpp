#include <mu/llvmc/ast.hpp>

#include <gc_cpp.h>

#include <mu/core/error_string.hpp>

mu::llvmc::ast::module::module ()
{
}

mu::llvmc::ast::result * mu::llvmc::ast::function::maybe_result (mu::llvmc::ast::node * node_a)
{
    auto result (dynamic_cast <mu::llvmc::ast::result *> (node_a));
    return result;
}

mu::llvmc::ast::expression * mu::llvmc::ast::function::maybe_expression (mu::llvmc::ast::node * node_a)
{
    auto result (dynamic_cast <mu::llvmc::ast::expression *> (node_a));
    return result;
}

mu::llvmc::ast::expression * mu::llvmc::ast::loop::as_expression (mu::llvmc::ast::node * node_a)
{
    assert (dynamic_cast <mu::llvmc::ast::expression *> (node_a) != nullptr);
    auto result (static_cast <mu::llvmc::ast::expression *> (node_a));
    return result;
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

mu::llvmc::ast::function_declaration::function_declaration (mu::llvmc::ast::node * node_a) :
function (node_a)
{
}

mu::llvmc::ast::array_type::array_type (mu::llvmc::ast::node * element_type_a, mu::llvmc::ast::node * size_a) :
element_type (element_type_a),
size (size_a)
{
}