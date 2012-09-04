#pragma once

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class definite_expression;
        }
        namespace runtime
        {
            class expression;
        }
        namespace synthesizer
        {
            class routine;
            class definite_expression
            {
            public:
                definite_expression (mu::script::synthesizer::routine & routine_a, mu::script::ast::definite_expression * expression_a);
                auto recurse (mu::script::synthesizer::routine & routine_a, mu::script::ast::definite_expression * expression_a) -> mu::script::runtime::expression *;
                mu::script::runtime::expression * expression_m;
            };
        }
    }
}