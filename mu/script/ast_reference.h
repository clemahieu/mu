#pragma once

#include <mu/script/ast_node.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class expression;
            class reference : public mu::script::ast::node
            {
            public:
                reference (mu::script::ast::expression * expression_a, size_t position_a);
                mu::script::ast::expression * expression;
                size_t position;
            };
        }
    }
}