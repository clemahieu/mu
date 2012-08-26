#pragma once

#include <mu/script/operation.h>

namespace mu
{
    namespace script
    {
        namespace runtime
        {
            class parameter : public mu::script::operation
            {
            public:
                parameter (size_t position_a);
                bool operator () (mu::script::context & context_a) override;
                size_t position;
            };
        }
    }
}