#include <mu/llvmc/wrapper.hpp>

#include <llvm/DerivedTypes.h>

mu::llvmc::wrapper::type::type (llvm::Type * type_a):
type_m (type_a)
{
}

mu::llvmc::wrapper::integer_type::integer_type (llvm::IntegerType * type_a):
type (type_a)
{
}

llvm::IntegerType * mu::llvmc::wrapper::integer_type::integer_value ()
{
    auto result (llvm::cast <llvm::IntegerType> (type_m));
    return result;
}