#pragma once

#include <mu/io/keywording/state.h>

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
                void operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) override;
                mu::io::keywording::keywording & keywording;
            };
        }
    }
}