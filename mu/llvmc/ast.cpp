#include <mu/llvmc/ast.hpp>

#include <mu/llvmc/availability.hpp>

#include <gc_cpp.h>

mu::llvmc::ast::node::~node ()
{
}

mu::llvmc::ast::base::base (mu::llvmc::availability::node * availability_a):
availability_m (availability_a)
{
}

mu::llvmc::ast::argument::argument (mu::llvmc::wrapper::type * type_a, mu::llvmc::availability::node * availability_a):
base (availability_a),
type (type_a)
{
}

mu::llvmc::ast::result::result (mu::llvmc::wrapper::type * type_a):
type (type_a),
value (nullptr)
{
}

mu::llvmc::ast::function::function (mu::llvmc::availability::module * availability_a):
base (availability_a)
{
}

mu::llvmc::ast::expression::expression (mu::llvmc::availability::node * availability_a):
base (availability_a)
{
}

mu::llvmc::ast::definite_expression::definite_expression (mu::llvmc::availability::node * availability_a):
expression (availability_a)
{
}


mu::llvmc::ast::value::value (mu::llvmc::availability::node * availability_a):
base (availability_a)
{
}

mu::llvmc::ast::module::module () :
base (new (GC) mu::llvmc::availability::module)
{
}

mu::llvmc::availability::node * mu::llvmc::ast::base::availability ()
{
    return availability_m;
}

mu::llvmc::availability::node * mu::llvmc::ast::result::availability ()
{
    return value->availability ();
}

mu::llvmc::ast::instruction::instruction (mu::llvmc::availability::module * availability_a, mu::llvmc::ast::instruction_type type_a):
base (availability_a),
type (type_a)
{
}