#include <mu/llvmc/wrapper.hpp>

#include <llvm/DerivedTypes.h>

mu::llvmc::wrapper::type::type (mu::llvmc::availability::node * availability_a, llvm::Type * type_a):
value (availability_a),
type_m (type_a)
{
}

mu::llvmc::wrapper::integer_type::integer_type (mu::llvmc::availability::node * availability_a, llvm::IntegerType * type_a)
: type (availability_a, type_a)
{
}

llvm::IntegerType * mu::llvmc::wrapper::integer_type::integer_value ()
{
    auto result (llvm::cast <llvm::IntegerType> (type_m));
    return result;
}