#pragma once

#include <mu/llvm_/ast_node.h>

namespace mu
{
    namespace llvm_
    {
        namespace ast
        {
            class parameter : public mu::llvm_::ast::node
            {
            public:
                parameter (size_t position_a);
                size_t position;
            };
        }
    }
}