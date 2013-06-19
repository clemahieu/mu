#pragma once

#include <mu/core/types.hpp>

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
        }
        namespace ast
        {
            class node;
            class expression;
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
        }
        class module_result
        {
        public:
            mu::llvmc::skeleton::module * module;
            mu::core::error * error;
        };
        class analyzer_module
        {
        public:
            analyzer_module ();
            module_result analyze (mu::llvmc::ast::node * module_a);
            bool process_global (mu::llvmc::ast::node * node_a);
            mu::map <mu::llvmc::ast::node *, mu::vector <mu::llvmc::skeleton::node *>> already_generated;
            mu::llvmc::skeleton::module * module;
            mu::llvmc::module_result result_m;
        };
        class function_result
        {
        public:
            mu::llvmc::skeleton::function * function;
            mu::core::error * error;
        };
        class analyzer_function
        {
        public:
            analyzer_function (mu::llvmc::analyzer_module & module_a);
            void process_parameters (mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s);
            void process_results (mu::llvmc::ast::function * function_a, mu::llvmc::skeleton::function * function_s);
            void process_node (mu::llvmc::ast::node * node_a);
            void process_element (mu::llvmc::ast::element * element_a);
            void process_value_call (mu::llvmc::ast::definite_expression * expression_a);
            void process_marker (mu::llvmc::ast::definite_expression * expression_a);
            void process_join (mu::llvmc::ast::definite_expression * expression_a);
            void process_asm (mu::llvmc::ast::definite_expression * expression_a);
            void process_array_type (mu::llvmc::ast::array_type * type_a);
            void process_constant_array (mu::llvmc::ast::constant_array * array_a);
            void process_identity (mu::llvmc::ast::definite_expression * expression_a);
            void process_call_values (mu::vector <mu::llvmc::ast::node *> const & arguments, size_t predicate_offset, mu::vector <mu::llvmc::skeleton::node *> & arguments_a, mu::llvmc::skeleton::branch * & most_specific_branch, size_t & predicate_position_a);
            void process_integer_type (mu::llvmc::ast::integer_type * type_a);
            void process_pointer_type (mu::llvmc::ast::pointer_type * type_a);
            void process_constant_int (mu::llvmc::ast::constant_int * constant_a);
			void process_loop (mu::llvmc::ast::loop * loop_a);
			void process_binary_integer_instruction (mu::llvmc::ast::definite_expression * expression_a, size_t predicate_offset, mu::vector <mu::llvmc::skeleton::node *> const & arguments, mu::llvmc::skeleton::branch * most_specific_branch);
            mu::llvmc::skeleton::number * process_number (mu::llvmc::ast::number * number_a);
            mu::llvmc::skeleton::value * process_value (mu::llvmc::ast::node * node_a);
            mu::llvmc::skeleton::type * process_type (mu::llvmc::ast::node * node_a);
            void process_definite_expression (mu::llvmc::ast::definite_expression * node_a);
            void process_single_node (mu::llvmc::ast::node * node_a);
            mu::set <mu::llvmc::ast::expression *> current_expression_generation;
            function_result analyze (mu::llvmc::ast::node * function_a);
            mu::llvmc::function_result result_m;
            mu::llvmc::analyzer_module & module;
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