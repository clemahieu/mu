#pragma once

namespace mu
{
    namespace core
    {
        namespace errors
        {
            class error_target;
        }
    }
    namespace llvm_
    {
        namespace ast
        {
            class expression;
        }
        namespace synthesizer
        {
            class expression
            {
            public:
                expression (mu::core::errors::error_target & errors_a, mu::llvm_::ast::expression * expression_a);
            };
        }
    }
}