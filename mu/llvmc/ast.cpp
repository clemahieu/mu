#include <mu/llvmc/ast.hpp>

#include <mu/llvmc/availability.hpp>

#include <gc_cpp.h>

mu::llvmc::ast::node::~node ()
{
}

mu::llvmc::ast::value::value (mu::llvmc::skeleton::node * node_a):
node_m (node_a)
{
}

mu::llvmc::ast::element::element (mu::llvmc::ast::node * node_a, size_t index_a):
node (node_a),
index (index_a)
{
}

mu::llvmc::ast::parameter::parameter (mu::llvmc::ast::node * type_a):
type (type_a)
{
}

mu::llvmc::ast::result::result (mu::llvmc::ast::node * written_type_a):
written_type (written_type_a),
value (nullptr)
{
}

mu::llvmc::ast::instruction::instruction (mu::llvmc::ast::instruction_type type_a):
type (type_a)
{
}