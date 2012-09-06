#pragma once

#include <mu/io/analyzer_state.h>

namespace mu
{
    namespace io
    {
        namespace analyzer
        {
            class error : public mu::io::analyzer::state
            {
                void operator () (mu::io::tokens::token const & token_a) override;
            };
        }
    }
}