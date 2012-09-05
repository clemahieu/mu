#pragma once

#include <mu/io/analyzer_state.h>

namespace mu
{
    namespace io
    {
        namespace keywording
        {
            class keywording;
            class begin : public mu::io::keywording::state
            {
            public:
                begin (mu::io::keywording::keywording & keywording_a);
                void operator () (mu::io::tokens::token * token_a) override;
                mu::io::keywording::keywording & keywording;
            };
        }
    }
}