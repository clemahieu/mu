#pragma once

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class expression;
        }
        namespace runtime
        {
            class expression;
        }
        namespace synthesizer
        {
            class routine;
            class expression
            {
            public:
                expression (mu::script::synthesizer::routine & routine_a, mu::script::ast::expression * expression_a);
                auto recurse (mu::script::synthesizer::routine & routine_a, mu::script::ast::expression * expression_a) -> mu::script::runtime::expression *;
                mu::script::runtime::expression * expression_m;
            };
        }
    }
}