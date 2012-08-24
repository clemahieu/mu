#pragma once

namespace mu
{
    namespace core
    {
        class node;
        namespace errors
        {
            class error_target;
        }
    }
    namespace llvm_
    {
        class ctx;
        namespace ast
        {
            class expression;
        }
        namespace value
        {
            class node;
        }
        namespace synthesizer
        {
            class routine;
            class expression
            {
            public:
                expression (mu::llvm_::ctx & ctx_a, mu::core::errors::error_target & errors_a, mu::llvm_::synthesizer::routine & routine_a, mu::llvm_::ast::expression * expression_a);
            };
        }
    }
}