#pragma once

#include <mu/script/ast_node.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class definite_expression;
            class reference : public mu::script::ast::node
            {
            public:
                reference (mu::script::ast::definite_expression * expression_a, size_t position_a);
                mu::script::ast::definite_expression * expression;
                size_t position;
            };
        }
    }
}