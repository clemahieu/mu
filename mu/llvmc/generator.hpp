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
            class module;
            class function;
        }
        class module_result
        {
        public:
            mu::llvmc::wrapper::module * module;
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
        class generator
        {
        public:
        };
    }
}