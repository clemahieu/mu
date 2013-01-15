#pragma once

#include <llvm/LLVMContext.h>

namespace llvm
{
    class Module;
}
namespace mu
{
    namespace core
    {
        class error;
    }
    namespace llvmc
    {
        namespace ast
        {
            class node;
        }
        class module_result
        {
        public:
            llvm::Module * module;
            mu::core::error * error;
        };
        class generator
        {
        public:
            llvm::LLVMContext context;
            module_result generate (mu::llvmc::ast::node * node_a);
        };
    }
}