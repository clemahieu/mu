#pragma once

#include <mu/core/types.h>

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
        namespace function
        {
            class node;
        }
        namespace module
        {
            class node;
        }
        namespace value
        {
            class node;
        }
        class ctx
        {
        public:
            ctx (mu::llvm_::context::node * context_a, mu::llvm_::module::node * module_a, mu::llvm_::function::node * function_a, mu::llvm_::basic_block::node * block_a);
            mu::vector <mu::llvm_::value::node *> working;
            mu::llvm_::context::node * context;
            mu::llvm_::module::node * module;
            mu::llvm_::function::node * function;
            mu::llvm_::basic_block::node * block;
        };
    }
}