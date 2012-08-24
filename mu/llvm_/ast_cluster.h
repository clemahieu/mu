#pragma once

#include <mu/llvm_/ast_node.h>

namespace mu
{
    namespace llvm_
    {
        namespace ast
        {
            class routine;
            class cluster : public mu::llvm_::ast::node
            {
            public:
                mu::vector <mu::llvm_::ast::routine *> routines;
            };
        }
    }
}