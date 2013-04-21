#pragma once

#include <mu/core/types.hpp>

#include <llvm/LLVMContext.h>

#include <boost/dynamic_bitset.hpp>

namespace llvm
{
    class Module;
    class Function;
    class Type;
    class BasicBlock;
    class Value;
    class PHINode;
    class Instruction;
    class ConstantInt;
    class TerminatorInst;
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
            class node;
            class switch_element;
            class constant_integer;
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
        class block;
        class terminator
        {
        public:
            virtual void terminate (llvm::BasicBlock * block_a) = 0;
            virtual bool is_exit ();
            mu::vector <mu::llvmc::block *> successors;
        };
        class generate_function;
        class terminator_return : public terminator
        {
        public:
            terminator_return (mu::llvmc::generate_function & generator_a);
            void terminate (llvm::BasicBlock * block_a) override;
            bool is_exit () override;
            mu::llvmc::generate_function & generator;
        };
        class branch;
        class terminator_jump : public terminator
        {
        public:
            void terminate (llvm::BasicBlock * block_a) override;
            mu::llvmc::branch * branch;
        };
        class terminator_switch : public terminator
        {
        public:
            terminator_switch (mu::llvmc::generate_function & generator_a, mu::llvmc::skeleton::value * predicate_a, mu::vector <mu::llvmc::skeleton::switch_element *> const & elements_a);
            void terminate (llvm::BasicBlock * block_a) override;
            mu::llvmc::generate_function & generator;
            mu::llvmc::skeleton::value * predicate;
            mu::vector <mu::llvmc::skeleton::switch_element *> elements;
        };
        class block
        {
        public:
            block (size_t order_a, llvm::TerminatorInst * terminator_a);
            block (size_t order_a, llvm::TerminatorInst * terminator_a, mu::llvmc::branch * branch_a);
            mu::llvmc::block * greatest (mu::llvmc::block * other);
            mu::llvmc::block * least (mu::llvmc::block * other);
            mu::llvmc::branch * branch;
            size_t order;
            llvm::TerminatorInst * terminator;
            mu::vector <mu::llvmc::block *> successors;
            mu::vector <mu::llvmc::block *> predecessors;
            llvm::BasicBlock * phis;
            llvm::BasicBlock * instructions;
        };
        class branch
        {
        public:
            branch (mu::llvmc::block * first_a, mu::llvmc::block * last_a, mu::llvmc::block * parent_a, llvm::ConstantInt * test_a);
            mu::llvmc::block * first;
            mu::llvmc::block * last;
            mu::llvmc::block * parent;
            llvm::ConstantInt * test;
        };
        enum class function_return_type
        {
            b0, // Unreachable
            b1v0, // Void
            b1v1, // Single value
            b1vm, // Struct no selector
            bmv0, // Selector value
            bmvm // struct with selector
        };
        class value_data
        {
        public:
            mu::llvmc::block * block;
            llvm::Value * value;
            mu::llvmc::value_data * forward_value;
        };
        class generate_function
        {
        public:
            generate_function (mu::llvmc::generate_module & module_a, mu::llvmc::skeleton::function * function_a);
            void generate ();
            llvm::Type * generate_type (mu::llvmc::skeleton::type * type_a);
            mu::llvmc::value_data * retrieve_value (mu::llvmc::skeleton::value * value_a);
            mu::llvmc::value_data * pull_value (mu::llvmc::branch * branch_a, mu::llvmc::skeleton::value * value_a);
            mu::llvmc::value_data * generate_value (mu::llvmc::skeleton::value * value_a);
            mu::llvmc::value_data * generate_single (mu::llvmc::skeleton::value * value_a);
            llvm::Value * generate_result_set (std::vector <llvm::Value *> const & undef_a);
            function_return_type get_return_type (mu::llvmc::skeleton::function * function_a);
            mu::llvmc::generate_module & module;
            llvm::Function * function_m;
            mu::llvmc::branch * body;
            llvm::BasicBlock * unreachable;
            mu::map <mu::llvmc::skeleton::value *, mu::llvmc::value_data *> already_generated;
            mu::llvmc::skeleton::function * function;
            function_return_type function_return_type;
        };
    }
}