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
        class generate_function;
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
            llvm::Value * predicate;
            llvm::Value * value;
        };
        class generate_function
        {
        public:
            generate_function (mu::llvmc::generate_module & module_a, mu::llvmc::skeleton::function * function_a);
            void generate ();
            llvm::Type * generate_type (mu::llvmc::skeleton::type * type_a);
            mu::llvmc::value_data retrieve_value (mu::llvmc::skeleton::value * value_a);
            mu::llvmc::value_data generate_value (mu::llvmc::skeleton::value * value_a);
            mu::llvmc::value_data generate_single (mu::llvmc::skeleton::value * value_a);
            void write_selector (llvm::LLVMContext & context, llvm::Value * & selector, uint8_t selector_number);
            llvm::Value * process_predicates (mu::vector <mu::llvmc::skeleton::node *> const & predicates_a);
            std::vector <llvm::Value *> generate_result_set ();
            function_return_type get_return_type (mu::llvmc::skeleton::function * function_a);
            mu::llvmc::generate_module & module;
            llvm::BasicBlock * last;
            llvm::Function * function_m;
            mu::map <mu::llvmc::skeleton::value *, mu::llvmc::value_data> already_generated;
            mu::llvmc::skeleton::function * function;
            function_return_type function_return_type;
        };
    }
}