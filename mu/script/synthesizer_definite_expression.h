#pragma once

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
            class definite_expression;
            class node;
        }
        namespace runtime
        {
            class definite_expression;
        }
        namespace synthesizer
        {
            class routine;
            class definite_expression
            {
            public:
                definite_expression (mu::script::synthesizer::routine & routine_a, mu::script::ast::definite_expression * expression_a);
                void recurse (mu::script::synthesizer::routine & routine_a, mu::core::node * node_a, mu::script::runtime::definite_expression * expression_a);
                auto recurse_expression (mu::script::synthesizer::routine & routine_a, mu::script::ast::definite_expression * expression_a) -> mu::script::runtime::definite_expression *;
            };
        }
    }
}