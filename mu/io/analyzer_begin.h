#pragma once

#include <mu/io/analyzer_state.h>

namespace mu
{
    namespace io
    {
        namespace analyzer
        {
            class analyzer;
            class begin : public mu::io::analyzer::state
            {
            public:
                begin (mu::io::analyzer::analyzer & analyzer_a);
                void operator () (mu::io::tokens::token * token_a) override;
                mu::io::analyzer::analyzer & analyzer;
            };
        }
    }
}