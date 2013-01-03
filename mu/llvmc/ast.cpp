#include <mu/llvmc/ast.hpp>

#include <mu/llvmc/availability.hpp>

#include <gc_cpp.h>

mu::llvmc::ast::node::~node ()
{
}

mu::llvmc::ast::scoped::scoped (mu::llvmc::availability::node * availability_a):
availability_m (availability_a)
{
}

mu::llvmc::ast::argument::argument (mu::llvmc::availability::node * availability_a):
scoped (availability_a)
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

mu::llvmc::ast::module::module () :
scoped (new (GC) mu::llvmc::availability::module)
{
}

mu::llvmc::availability::module * mu::llvmc::ast::module::availability ()
{
    auto result_node (availability_m);
    assert (dynamic_cast <mu::llvmc::availability::module *> (result_node));
    auto result (static_cast <mu::llvmc::availability::module *> (result_node));
    return result;
}