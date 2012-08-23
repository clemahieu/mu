#pragma once

#include <mu/llvm_/ast_node.h>

namespace mu
{
    namespace llvm_
    {
        namespace function
        {
            class node;
        }
        namespace ast
        {
            class expression;
            class routine : public mu::llvm_::ast::node
            {
            public:
                routine ();
                mu::llvm_::function::node * function;
                mu::llvm_::ast::expression * body;
            };
        }
    }
}