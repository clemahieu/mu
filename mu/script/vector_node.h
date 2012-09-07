#pragma once

#include <mu/core/node.h>
#include <mu/core/types.h>

namespace mu
{
    namespace script
    {
        namespace vector
        {
            class node : public mu::core::node
            {
            public:
                mu::vector <mu::core::node *> vector;
            };
        }
    }
}