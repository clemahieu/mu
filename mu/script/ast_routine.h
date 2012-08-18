#pragma once

#include <mu/script/ast_node.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class expression;
            class routine : public mu::script::ast::node
            {
            public:
                mu::script::ast::expression * body;
            };
        }
    }
}