#pragma once

#include <mu/core/types.h>

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
        namespace argument
        {
            class node;
        }
        namespace ast
        {
            class expression;
            class routine;
        }
        namespace context
        {
            class node;
        }
        namespace function
        {
            class node;
        }
        namespace module
        {
            class node;
        }
        namespace synthesizer
        {
            class cluster;
            class routine
            {
            public:
                routine (mu::llvm_::synthesizer::cluster & cluster_a, mu::llvm_::context::node * context_a, mu::llvm_::module::node * module_a, mu::core::errors::error_target & errors_a, mu::llvm_::ast::routine * routine_a);
                mu::llvm_::function::node * routine_m;
                mu::vector <mu::llvm_::argument::node *> arguments;
                mu::map <mu::llvm_::ast::expression *, mu::core::node *> already_parsed;
                mu::set <mu::llvm_::ast::expression *> current_cycle;
            };
        }
    }
}