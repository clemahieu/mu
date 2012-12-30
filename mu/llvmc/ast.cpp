#include <mu/llvmc/ast.hpp>

#include <mu/llvmc/availability.hpp>

mu::llvmc::ast::node::~node ()
{
}

mu::llvmc::ast::scoped::scoped (mu::llvmc::availability::node * availability_a):
availability (availability_a)
{
}

mu::llvmc::ast::function::function (mu::llvmc::availability::module * availability_a):
scoped (availability_a)
{
}

mu::llvmc::ast::expression::expression (mu::llvmc::availability::node * availability_a):
scoped (availability_a)
{
}