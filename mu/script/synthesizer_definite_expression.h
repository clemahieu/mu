#pragma once

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class definite_expression;
            class node;
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
                void recurse (mu::script::synthesizer::routine & routine_a, mu::script::ast::node * node_a, mu::script::runtime::expression * expression_a);
                auto recurse_expression (mu::script::synthesizer::routine & routine_a, mu::script::ast::definite_expression * expression_a) -> mu::script::runtime::expression *;
            };
        }
    }
}