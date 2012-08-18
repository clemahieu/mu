#pragma once

#include <mu/script/ast_node.h>
#include <mu/core/node_list.h>

namespace mu
{
    namespace core
    {
        class node;
    }
    namespace script
    {
        namespace ast
        {
            class expression : public mu::script::ast::node
            {
            public:
                mu::core::node_list nodes;
            };
        }
    }
}