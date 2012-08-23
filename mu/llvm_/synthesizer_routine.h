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
            class routine;
        }
        namespace function
        {
            class node;
        }
        namespace synthesizer
        {
            class routine
            {
            public:
                routine (mu::core::errors::error_target & errors_a, mu::llvm_::ast::routine * routine_a);
                mu::llvm_::function::node * routine_m;
            };
        }
    }
}