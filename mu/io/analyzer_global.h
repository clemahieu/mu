#pragma once

#include <mu/io/analyzer_state.h>

namespace mu
{
    namespace core
    {
        class node;
    }
    namespace io
    {
        namespace analyzer
        {
            class analyzer;
            class global : public mu::io::analyzer::state
            {
            public:
                global (mu::io::analyzer::analyzer & analyzer_a, mu::core::node * node_a);
                void operator () (mu::io::tokens::token * token_a) override;
                mu::io::analyzer::analyzer & analyzer;
                mu::core::node * node;
            };
        }
    }
}