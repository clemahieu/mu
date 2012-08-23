#pragma once

#include <mu/core/types.h>

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
            class cluster;
            class routine;
        }
        namespace cluster
        {
            class node;
        }
        namespace context
        {
            class node;
        }
        namespace function
        {
            class node;
        }
        namespace synthesizer
        {
            class cluster
            {
            public:
                cluster (mu::llvm_::context::node * context_a, mu::core::errors::error_target & errors_a, mu::llvm_::ast::cluster * cluster_a);
                mu::map <mu::llvm_::ast::routine *, mu::llvm_::function::node *> routines;
                mu::llvm_::cluster::node * cluster_m;
            };
        }
    }
}