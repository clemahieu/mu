#pragma once

#include <mu/llvm_/ast_node.h>

namespace mu
{
    namespace llvm_
    {
        namespace type
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
                mu::vector <mu::llvm_::type::node *> results;
                mu::vector <mu::llvm_::type::node *> types;
                mu::llvm_::ast::expression * body;
            };
        }
    }
}