#pragma once

#include <mu/llvmc/ast.hpp>

namespace llvm
{
    class Type;
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
                llvm::Type * type;
            };
        }
    }
}