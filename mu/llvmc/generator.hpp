#pragma once

#include <mu/core/types.hpp>

#include <llvm/LLVMContext.h>

#include <vector>

namespace llvm
{
    class Module;
    class Function;
    class Type;
    class BasicBlock;
    class Value;
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
            class expression;
        }
        namespace wrapper
        {
            class value;
        }
        class module_result
        {
        public:
            llvm::Module * module;
            mu::core::error * error;
        };
        class branch
        {
        public:
            size_t index;
            llvm::BasicBlock * first;
            llvm::BasicBlock * last;
            mu::set <mu::llvmc::ast::node *> values;
        };
        class body_generator
        {
        public:
            body_generator (mu::llvmc::ast::function * ast_a, llvm::Function * function_a);
            void generate ();
            mu::map <mu::llvmc::ast::node *, std::pair <llvm::Value *, mu::llvmc::branch *>> complete;
            decltype (complete)::mapped_type generate_value (mu::llvmc::ast::node * node_a);
            mu::set <mu::llvmc::ast::node *> generating;
            size_t last_branch;
            mu::llvmc::branch entry;
            mu::llvmc::ast::function * ast;
            mu::core::error * error;
            llvm::Function * function;
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