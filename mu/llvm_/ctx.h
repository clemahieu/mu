#pragma once

#include <mu/core/context.h>

namespace mu
{
    namespace llvm_
    {
        namespace basic_block
        {
            class node;
        }
        namespace context
        {
            class node;
        }
        class ctx : public mu::core::context
        {
        public:
            ctx (mu::llvm_::context::node * context_a, mu::llvm_::basic_block::node * block_a);
            mu::llvm_::context::node * context;
            mu::llvm_::basic_block::node * block;
        };
    }
}