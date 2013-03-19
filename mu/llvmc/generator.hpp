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
            virtual void terminate (llvm::BasicBlock * block_a) = 0;
        };
        class generate_function;
        class terminator_return : public terminator
        {
        public:
            terminator_return (mu::llvmc::generate_function & generator_a);
            void terminate (llvm::BasicBlock * block_a) override;
            mu::llvmc::generate_function & generator;
        };
        class join
        {
        public:
        };
        class branch
        {
        public:
            branch (llvm::BasicBlock * block_a, size_t order_a, mu::llvmc::branch * next_branch, mu::llvmc::terminator * terminator);
            llvm::BasicBlock * block;
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
            mu::llvmc::value_data retrieve_value (mu::llvmc::skeleton::value * value_a);
            mu::llvmc::value_data generate_value (mu::llvmc::skeleton::value * value_a);
            mu::llvmc::value_data generate_local_value (mu::llvmc::skeleton::value * value_a);
            mu::llvmc::value_data insert_value (mu::llvmc::skeleton::value * value_a, mu::llvmc::branch * branch_a, llvm::Value * val_a);
            void set_bit_and_successors (size_t bit_a, mu::llvmc::branch * branch_a);
            mu::llvmc::generate_module & module;
            mu::llvmc::branch * entry;
            llvm::Function * function_m;
            mu::map <mu::llvmc::skeleton::branch *, mu::llvmc::branch *> branches;
            mu::map <mu::llvmc::skeleton::value *, value_data> already_generated;
            mu::llvmc::skeleton::function * function;
        };
    }
}