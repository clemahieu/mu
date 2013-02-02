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
            class type;
        }
        class module_result
        {
        public:
            llvm::Module * module;
            mu::core::error * error;
        };
        class branch;
        class terminator
        {
        public:
            virtual void generate (llvm::BasicBlock * block_a);
            mu::vector <mu::llvmc::branch *> successors;
        };
        class phi
        {
        public:
        };
        class branch
        {
        public:
            branch ();
            size_t order;
            mu::llvmc::branch * next;
            mu::llvmc::terminator * terminator;
            mu::vector <mu::llvmc::phi *> phi_nodes;
            std::vector <llvm::Instruction *> instructions;
            mu::set <mu::llvmc::branch *> predecessors;
            std::vector <bool> variables;
        };
        class body_generator
        {
        public:
            body_generator (mu::llvmc::ast::function * ast_a, llvm::Function * function_a);
            void generate ();
            mu::llvmc::branch entry;
            mu::map <mu::llvmc::ast::node *, std::pair <size_t, mu::llvmc::branch *>> values;
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
            void generate (mu::llvmc::ast::node * node_a);
            void generate_function (mu::llvmc::ast::function * function_a);
        };
    }
}