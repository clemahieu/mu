#pragma once

#include <mu/io/keywording/state.h>

namespace mu
{
    namespace core
    {
        class node;
    }
    namespace io
    {
        namespace keywording
        {
            class keywording;
            class global : public mu::io::keywording::state
            {
            public:
                global (mu::io::keywording::keywording & keywording_a, mu::core::node * node_a);
                void operator () (mu::io::tokens::token * token_a) override;
                mu::io::keywording::keywording & keywording;
                mu::core::node * node;
            };
        }
    }
}