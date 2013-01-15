#pragma once

#include <llvm/LLVMContext.h>

#include <vector>

namespace llvm
{
    class Module;
    class Function;
    class Type;
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
            class function;
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
            generator ();
            mu::llvmc::module_result result;
            llvm::LLVMContext context;
            llvm::Module * module;
            llvm::Function * function;
            void generate (mu::llvmc::ast::node * node_a);
            void generate_function (mu::llvmc::ast::function * function_a);
        };
    }
}