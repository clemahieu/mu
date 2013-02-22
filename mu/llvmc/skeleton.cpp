#include <mu/llvmc/skeleton.hpp>

mu::llvmc::skeleton::element::element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::call * call_a, size_t index_a) :
value (branch_a),
call (call_a),
index (index_a)
{
}

mu::llvmc::skeleton::node::~node ()
{
}

mu::llvmc::skeleton::function::function () :
value (nullptr),
entry (nullptr)
{
}

mu::llvmc::skeleton::branch::branch (mu::llvmc::skeleton::branch * parent_a) :
parent (parent_a)
{
}

mu::llvmc::skeleton::value::value (mu::llvmc::skeleton::branch * branch_a) :
branch (branch_a)
{
}

mu::llvmc::skeleton::integer_type::integer_type (size_t bits_a) :
bits (bits_a)
{
}

mu::llvmc::skeleton::parameter::parameter (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a) :
value (branch_a),
type (type_a)
{
}

mu::llvmc::skeleton::result::result (mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * value_a):
type (type_a),
value (value_a)
{
}

mu::llvmc::skeleton::instruction::instruction (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::instruction_type type_a) :
value (branch_a),
type (type_a)
{
}