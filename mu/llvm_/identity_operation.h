#pragma once

#include <mu/llvm_/operation.h>
#include <mu/core/node.h>

namespace mu
{
    namespace llvm_
    {
        namespace identity
        {
            class operation : public mu::llvm_::operation, public mu::core::node
            {
            public:
                bool operator () (mu::llvm_::ctx & context_a) override;
            };
        }
    }
}