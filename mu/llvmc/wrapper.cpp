#include <mu/llvmc/wrapper.hpp>

#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

mu::llvmc::wrapper::value::value (llvm::Value * value_a):
value_m (value_a)
{
}

mu::llvmc::wrapper::integer_type::integer_type (llvm::IntegerType * type_a):
type_m (type_a)
{
}

llvm::Type * mu::llvmc::wrapper::integer_type::real_type ()
{
    return type_m;
}

llvm::Type * mu::llvmc::wrapper::group_type::real_type ()
{
    std::vector <llvm::Type *> types;
    for (auto i (elements.begin ()), j (elements.end ()); i != j; ++i)
    {
        types.push_back ((*i)->real_type ());
    }
    auto result (llvm::StructType::get (context, types));
    return result;
}

llvm::Type * mu::llvmc::wrapper::set_type::real_type ()
{
    std::vector <llvm::Type *> types;
    for (auto i (elements.begin ()), j (elements.end ()); i != j; ++i)
    {
        types.push_back ((*i)->real_type ());
    }
    auto result (llvm::StructType::get (context, types));
    return result;
}

llvm::Type * mu::llvmc::wrapper::branch_type::real_type ()
{
    std::vector <llvm::Type *> types;
    types.push_back (selector->real_type ());
    for (auto i (elements.begin ()), j (elements.end ()); i != j; ++i)
    {
        types.push_back ((*i)->real_type ());
    }
    auto result (llvm::StructType::get (context, types));
    return result;
}