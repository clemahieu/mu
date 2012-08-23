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
    namespace script
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
        namespace runtime
        {
            class routine;
        }
        namespace synthesizer
        {
            class cluster
            {
            public:
                cluster (mu::core::errors::error_target & errors_a, mu::script::ast::cluster * cluster_a);
                mu::map <mu::script::ast::routine *, mu::script::runtime::routine *> routines;
                mu::script::cluster::node * cluster_m;
            };
        }
    }
}