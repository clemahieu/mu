#pragma once

#include <mu/script/ast_node.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class definite_expression;
            class routine : public mu::script::ast::node
            {
            public:
                routine ();
                mu::string name;
                mu::script::ast::definite_expression * body;
            };
        }
    }
}