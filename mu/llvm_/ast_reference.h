#pragma once

#include <mu/llvm_/ast_node.h>

namespace mu
{
    namespace llvm_
    {
        namespace ast
        {
            class expression;
            class reference : public mu::llvm_::ast::node
            {
            public:
                reference (mu::llvm_::ast::expression * expression_a, size_t position_a);
                mu::llvm_::ast::expression * expression;
                size_t position;
            };
        }
    }
}