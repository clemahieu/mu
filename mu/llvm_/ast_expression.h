#pragma once

#include <mu/llvm_/ast_node.h>
#include <mu/core/node_list.h>

namespace mu
{
    namespace llvm_
    {
        namespace ast
        {
            class expression : public mu::llvm_::ast::node
            {
            public:
                mu::core::node_list nodes;
            };
        }
    }
}