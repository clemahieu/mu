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
                routine ();
                mu::string name;
                mu::script::ast::expression * body;
            };
        }
    }
}