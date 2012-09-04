#pragma once

#include <mu/script/ast_expression.h>
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
            class definite_expression : public mu::script::ast::expression
            {
            public:
                mu::core::node_list nodes;
            };
        }
    }
}