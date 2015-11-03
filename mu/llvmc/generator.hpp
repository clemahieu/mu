#pragma once

#include <tuple>

#include <mu/core/types.hpp>
#include <mu/llvmc/skeleton.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/DebugInfoMetadata.h>

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
	class DIBuilder;
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
            class function_call;
			class constant;
            enum class function_return_type;
        }
        class generator_result
        {
        public:
            llvm::Function * entry;
            std::unique_ptr <llvm::Module> module;
        };
        class generator
        {
        public:
            mu::llvmc::generator_result generate (llvm::LLVMContext & context_a, mu::llvmc::skeleton::module * module_a, mu::string const & name_a, mu::string const & path_a, uint64_t module_id_a);
        };
		class generate_system : public mu::llvmc::skeleton::visitor
		{
		public:
			generate_system (llvm::LLVMContext & context_a, mu::string const & name_a, mu::string const & path_a, uint64_t module_id_a);
            void generate_value (mu::llvmc::skeleton::value * node_a);
			void generate_type (mu::llvmc::skeleton::type * node_a);
			void module (mu::llvmc::skeleton::module * node_a) override;
			mu::llvmc::skeleton::visitor * current_generator;
			mu::string const & name;
			mu::string const & path;
			uint64_t module_id;
			mu::llvmc::generator_result result;
		};
        class generate_module : public mu::llvmc::skeleton::visitor
        {
        public:
            generate_module (mu::llvmc::generate_system & system_a, mu::llvmc::skeleton::module * module_a);
			~generate_module ();
			void constant_aggregate_zero (mu::llvmc::skeleton::constant_aggregate_zero * node_a) override;
            void unit_value (mu::llvmc::skeleton::unit_value * node_a) override;
			void constant_array (mu::llvmc::skeleton::constant_array * constant_array) override;
			void constant_pointer_null (mu::llvmc::skeleton::constant_pointer_null * value_a) override;
			void constant_integer (mu::llvmc::skeleton::constant_integer * constant_int) override;
			void global_variable (mu::llvmc::skeleton::global_variable * global_variable) override;
			void undefined (mu::llvmc::skeleton::undefined * node_a) override;
			void function (mu::llvmc::skeleton::function * node_a) override;
			void named (mu::llvmc::skeleton::named * node_a) override;
			void integer_type (mu::llvmc::skeleton::integer_type * integer_type) override;
			void pointer_type (mu::llvmc::skeleton::pointer_type * pointer_type) override;
			void unit_type (mu::llvmc::skeleton::unit_type * unit_type) override;
			void function_type (mu::llvmc::skeleton::function_type * function_type_a) override;
			void fixed_array_type (mu::llvmc::skeleton::fixed_array_type * array_type) override;
			void struct_type (mu::llvmc::skeleton::struct_type * struct_type) override;
			void node (mu::llvmc::skeleton::node * node_a) override;
			std::string get_global_name (mu::string const & name_a);
            void generate ();
			llvm::DIBuilder builder;
            mu::llvmc::skeleton::module * module;
			llvm::DIFile * file;
            uint64_t global_id;
			mu::llvmc::skeleton::visitor * previous;
			mu::llvmc::generate_system & system;
        };
        class generate_function : public mu::llvmc::skeleton::visitor
        {
        public:
            generate_function (mu::llvmc::generate_module & module_a, mu::llvmc::skeleton::function * function_a);
			~generate_function ();
			void call_element (mu::llvmc::skeleton::call_element * node_a) override;
			void loop_element (mu::llvmc::skeleton::loop_element * loop_element) override;
			void identity_element (mu::llvmc::skeleton::identity_element * identity_value) override;
			void join_element (mu::llvmc::skeleton::join_element * join) override;
            void inline_asm (mu::llvmc::skeleton::inline_asm * asm_l) override;
			void switch_element (mu::llvmc::skeleton::switch_element * element) override;
            void named (mu::llvmc::skeleton::named * named) override;
			void instruction (mu::llvmc::skeleton::instruction * instruction) override;
			void icmp (mu::llvmc::skeleton::icmp * icmp) override;
			void store (mu::llvmc::skeleton::store * store) override;
			void node (mu::llvmc::skeleton::node * node_a) override;
            void generate_loop_arguments (mu::llvmc::skeleton::loop_element * loop_element, llvm::Value * & loop_predicate);
            void generate ();
            llvm::Value * generate_rejoin (llvm::BasicBlock * entry, llvm::BasicBlock * predicate, llvm::BasicBlock * successor, llvm::Value * value_a);
            void write_selector (llvm::LLVMContext & context, llvm::Value * & selector, uint8_t selector_number);
            llvm::Value * process_predicates (llvm::Value * predicate_a, mu::vector <mu::llvmc::skeleton::value *> const & arguments_a);
            llvm::Value * and_predicates (llvm::Value * left_a, llvm::Value * right_a);
            std::vector <llvm::Value *> generate_result_set ();
            mu::llvmc::generate_module & module;
            llvm::BasicBlock * last;
            llvm::Function * function_m;
            mu::llvmc::skeleton::function * function;
            mu::llvmc::skeleton::function_return_type function_return_type;
            llvm::DILexicalBlock * block_d;
			mu::llvmc::skeleton::visitor * previous;
        };
    }
}