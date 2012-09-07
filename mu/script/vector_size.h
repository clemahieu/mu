#pragma once

#include <mu/script/operation.h>

namespace mu
{
    namespace script
    {
        namespace vector
        {
            class size : public mu::script::operation
            {
            public:
                bool operator () (mu::script::context & context_a) override;
            };
        }
    }
}