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
    class PHINode;
    class Instruction;
}
namespace mu
{
    namespace core
    {
        class error;
    }
    namespace llvmc
    {
        namespace skeleton
        {
            class module;
            class function;
            class type;
            class value;
            class branch;
        }
        class generator
        {
        public:
            llvm::Module * generate (llvm::LLVMContext & context_a, mu::llvmc::skeleton::module * module_a);
        };
        class generate_module
        {
        public:
            generate_module (mu::llvmc::skeleton::module * module_a, llvm::Module * target_a);
            void generate ();
            mu::map <mu::llvmc::skeleton::function *, llvm::Function *> functions;
            mu::llvmc::skeleton::module * module;
            llvm::Module * target;
        };
        class terminator
        {
        public:
        };
        class join
        {
        public:
        };
        class branch
        {
        public:
            branch (size_t order_a, mu::llvmc::branch * next_branch, mu::llvmc::terminator * terminator);
            size_t order;
            mu::llvmc::branch * next_branch;
            mu::llvmc::terminator * terminator;
            std::vector <llvm::PHINode *> phi_nodes;
            std::vector <llvm::Instruction *> instructions;
            mu::vector <mu::llvmc::branch *> predecessors;
            mu::vector <mu::llvmc::branch *> successors;
            std::vector <bool> available_variables;
        };
        class value_data
        {
        public:
            size_t bit_index;
            llvm::Value * value;
            mu::llvmc::branch * branch;
        };
        class generate_function
        {
        public:
            generate_function (mu::llvmc::generate_module & module_a, mu::llvmc::skeleton::function * function_a);
            void generate ();
            llvm::Type * generate_type (mu::llvmc::skeleton::type * type_a);
            llvm::Value * retrieve_value (mu::llvmc::skeleton::value * value_a);
            llvm::Value * create (mu::llvmc::skeleton::value * value_a);
            mu::llvmc::generate_module & module;
            llvm::Function * function_m;
            mu::map <mu::llvmc::skeleton::branch *, mu::llvmc::branch *> branches;
            mu::map <mu::llvmc::skeleton::value *, value_data> already_generated;
            mu::llvmc::skeleton::function * function;
        };
    }
}