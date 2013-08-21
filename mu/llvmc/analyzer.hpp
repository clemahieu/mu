#pragma once

#include <mu/core/types.hpp>

#include "ast.hpp"

namespace mu
{
    namespace core
    {
        class error;
        class region;
    }
    namespace llvmc
    {
        namespace skeleton
        {
            class value;
            class node;
            class module;
            class expression;
            class function;
            class type;
            class branch;
            class number;
            class global_value;
        }
        namespace ast
        {
            class node;
            class definite_expression;
            class function;
            class instruction;
            class element;
            class integer_type;
            class pointer_type;
            class constant_int;
            class number;
			class loop;
            class asm_c;
            class array_type;
            class constant_array;
            class join;
        }
        class module_result
        {
        public:
            mu::llvmc::skeleton::module * module;
            mu::core::error * error;
        };
        class function_result
        {
        public:
            mu::llvmc::skeleton::function * function;
            mu::core::error * error;
        };
		class module_processor;
        class function_processor : public mu::llvmc::ast::visitor
        {
        public:
            function_processor (mu::llvmc::module_processor & module_a, mu::core::error * & error_a, mu::llvmc::skeleton::branch * entry_a);
            void process_node (mu::llvmc::ast::node * node_a);
            void process_value_call (mu::llvmc::ast::definite_expression * expression_a);
            void process_marker (mu::llvmc::ast::definite_expression * expression_a);
            void process_asm (mu::llvmc::ast::definite_expression * expression_a);
            void process_identity (mu::llvmc::ast::definite_expression * expression_a);
            void process_call_values (mu::vector <mu::llvmc::ast::node *> const & arguments, size_t predicate_offset, mu::vector <mu::llvmc::skeleton::node *> & arguments_a, mu::llvmc::skeleton::branch * & most_specific_branch, size_t & predicate_position_a);
			void process_binary_integer_instruction (mu::llvmc::ast::definite_expression * expression_a, size_t predicate_offset, mu::vector <mu::llvmc::skeleton::node *> const & arguments, mu::llvmc::skeleton::branch * most_specific_branch);
            mu::llvmc::skeleton::number * process_number (mu::llvmc::ast::number * number_a);
            mu::llvmc::skeleton::value * process_value (mu::llvmc::ast::node * node_a);
            mu::llvmc::skeleton::type * process_type (mu::llvmc::ast::node * node_a);
            void process_definite_expression (mu::llvmc::ast::definite_expression * node_a);
            void process_single_node (mu::llvmc::ast::node * node_a);
            void node (mu::llvmc::ast::node * node_a) override;
			void value (mu::llvmc::ast::value * value_node) override;
			void integer_type (mu::llvmc::ast::integer_type * type_a) override;
			void element (mu::llvmc::ast::element * element_a) override;
			void unit (mu::llvmc::ast::unit * node_a) override;
			void constant_int (mu::llvmc::ast::constant_int * constant_a) override;
			void pointer_type (mu::llvmc::ast::pointer_type * type_a) override;
			void asm_c (mu::llvmc::ast::asm_c * asm_l) override;
			void number (mu::llvmc::ast::number * node_a) override;
			void array_type (mu::llvmc::ast::array_type * type_a) override;
			void constant_array (mu::llvmc::ast::constant_array * array_a) override;
			void global_variable (mu::llvmc::ast::global_variable * global_variable) override;
			void constant_pointer_null (mu::llvmc::ast::constant_pointer_null * constant_pointer_null) override;
			void unit_type (mu::llvmc::ast::unit_type * unit_type) override;
			void join (mu::llvmc::ast::join * node_a) override;
			void function (mu::llvmc::ast::function * function_node) override;
			void loop (mu::llvmc::ast::loop * loop_a) override;
			void definite_expression (mu::llvmc::ast::definite_expression * expression_a) override;
            void struct_type (mu::llvmc::ast::struct_type * node_a) override;
			void undefined (mu::llvmc::ast::undefined * node_a) override;
			void template_c (mu::llvmc::ast::template_c * node_a) override;
            void entry (mu::llvmc::ast::entry * node_a) override;
			void process_template (mu::llvmc::ast::definite_expression * node_a);
            void process_parameters (mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s);
            void process_results (mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s);
            mu::llvmc::module_processor & module;
            mu::core::error * & error;
            mu::llvmc::skeleton::branch * entry_m;
			mu::llvmc::ast::visitor * current_context;
        };
		class branch_analyzer
		{
		public:
			branch_analyzer (mu::llvmc::skeleton::branch * global_a, mu::core::error * & result_a);
            mu::llvmc::skeleton::branch * add_branch (mu::llvmc::skeleton::branch * branch_a, mu::core::region const & region_a);
			void new_set ();
			mu::llvmc::skeleton::branch * global;
			mu::llvmc::skeleton::branch * most_specific;
			mu::set <mu::llvmc::skeleton::branch *> ancestors;
			mu::set <mu::llvmc::skeleton::branch *> leaves;
			mu::core::error * & result;
		};
        class analyzer
        {
        public:
            module_result analyze (mu::llvmc::ast::node * module_a);
        };
    }
}