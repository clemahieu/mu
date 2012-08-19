#pragma once

#include <mu/core/node.h>

namespace mu
{
    namespace script
    {
        namespace ast
        {
            class parameters : public mu::core::node
            {
            public:
                parameters (size_t parameter_a);
                size_t parameter;
            };
        }
    }
}