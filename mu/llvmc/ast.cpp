#include <mu/llvmc/ast.hpp>

#include <mu/llvmc/availability.hpp>

#include <gc_cpp.h>

mu::llvmc::ast::node::~node ()
{
}

mu::llvmc::ast::argument::argument (mu::llvmc::wrapper::type * type_a):
type (type_a)
{
}

mu::llvmc::ast::result::result (mu::llvmc::wrapper::type * written_type_a):
written_type (written_type_a),
value (nullptr)
{
}

mu::llvmc::ast::instruction::instruction (mu::llvmc::ast::instruction_type type_a):
type (type_a)
{
}