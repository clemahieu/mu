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
            class routine;
            class expression;
        }
        namespace runtime
        {
            class routine;
            class expression;
        }
        namespace synthesizer
        {
            class cluster;
            class routine
            {
            public:
                routine (mu::core::errors::error_target & errors_a, mu::script::synthesizer::cluster & cluster_a, mu::script::ast::routine * routine_a);
                mu::core::errors::error_target & errors;
                mu::script::runtime::routine * routine_m;
                mu::script::synthesizer::cluster & cluster;
                mu::map <mu::script::ast::expression *, mu::script::runtime::expression *> already_parsed;
                mu::set <mu::script::ast::expression *> current_cycle;
            };
        }
    }
}