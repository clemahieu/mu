#pragma once

#include <mu/io/keywording_state.h>

namespace mu
{
    namespace io
    {
        namespace keywording
        {
            class error : public mu::io::keywording::state
            {
                void operator () (mu::io::tokens::token * token_a) override;
            };
        }
    }
}