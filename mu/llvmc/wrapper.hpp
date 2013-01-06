#pragma once

#include <mu/llvmc/ast.hpp>

namespace llvm
{
    class Type;
    class IntegerType;
}
namespace mu
{
    namespace llvmc
    {
        namespace wrapper
        {
            class type : public mu::llvmc::ast::value
            {
            public:
                type (mu::llvmc::availability::node * availability_a, llvm::Type * type_a);
                llvm::Type * type_m;
            };
            class integer_type : public mu::llvmc::wrapper::type
            {
            public:
                integer_type (mu::llvmc::availability::node * availability_a, llvm::IntegerType * type_a);
                llvm::IntegerType * integer_value ();
            };
        }
    }
}