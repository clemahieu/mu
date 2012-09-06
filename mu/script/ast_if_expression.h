#pragma once

#include <mu/script/ast_expression.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class definite_expression;
            class if_expression : public mu::script::ast::expression
            {
            public:
                if_expression ();
                mu::script::ast::definite_expression * predicate;
                mu::script::ast::definite_expression * true_branch;
                mu::script::ast::definite_expression * false_branch;
            };
        }
    }
}