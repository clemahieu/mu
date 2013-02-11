#include <mu/llvmc/skeleton.hpp>

mu::llvmc::skeleton::element::element (mu::llvmc::skeleton::expression * expression_a, size_t index_a) :
expression_m (expression_a),
index (index_a)
{
}

mu::llvmc::skeleton::expression::~expression ()
{
}

mu::llvmc::skeleton::integer_type::integer_type (size_t bits_a) :
bits (bits_a)
{
}

mu::llvmc::skeleton::parameter::parameter (mu::llvmc::skeleton::type * type_a) :
type (type_a)
{
}