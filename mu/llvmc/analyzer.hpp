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
            class function;
            class type;
            class branch;
            class number;
            class global_value;
        }
        namespace ast
        {
            class node;
            class expression;
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
		class global_processor : public mu::llvmc::ast::visitor
		{
		public:
			global_processor (mu::core::error * & error_a);
            void process_node (mu::llvmc::ast::node * node_a);
			void node (mu::llvmc::ast::node * node_a) override;
			void module (mu::llvmc::ast::module * node_a) override;
			void number (mu::llvmc::ast::number * node_a) override;
			void template_parameter (mu::llvmc::ast::template_parameter * node_a) override;
			mu::llvmc::skeleton::number * process_number (mu::llvmc::ast::node *);
			std::string print_analysis_stack ();
			mu::vector <mu::llvmc::ast::node *> analysis_stack;
			mu::llvmc::ast::visitor * current_context;
			mu::core::error * & error;
            mu::llvmc::skeleton::branch * current_origin;
		};
		class module_processor : public mu::llvmc::ast::visitor
		{
		public:
			module_processor (mu::llvmc::global_processor &);
			~module_processor ();
			void function (mu::llvmc::ast::function *) override;
			void function_overload (mu::llvmc::ast::function_overload *) override;
			void function_family (mu::llvmc::ast::function_family *) override;
			void node (mu::llvmc::ast::node *) override;
			void element (mu::llvmc::ast::element *) override;
			void set (mu::llvmc::ast::set *) override;
            void entry (mu::llvmc::ast::entry *) override;
			void fixed_array_type (mu::llvmc::ast::fixed_array_type *) override;
			void integer_type (mu::llvmc::ast::integer_type *) override;
			void pointer_type (mu::llvmc::ast::pointer_type *) override;
			void unit_type (mu::llvmc::ast::unit_type *) override;
            void struct_type (mu::llvmc::ast::struct_type *) override;
            void process_single_node (mu::llvmc::ast::node *);
			void global_variable (mu::llvmc::ast::global_variable *) override;
			void constant_int (mu::llvmc::ast::constant_int *) override;
			void constant_array (mu::llvmc::ast::constant_array *) override;
			void constant_pointer_null (mu::llvmc::ast::constant_pointer_null *) override;
			void expression (mu::llvmc::ast::expression *) override;
            void process_identity (mu::llvmc::ast::expression *);
			void template_c (mu::llvmc::ast::template_c *) override;
			void value (mu::llvmc::ast::value *) override;
			void process_template (mu::llvmc::ast::expression *);
            void process_expression_value_arguments (mu::vector <mu::llvmc::ast::node *> const &, mu::vector <mu::llvmc::skeleton::node *> &, mu::vector <mu::llvmc::skeleton::value *> &, mu::llvmc::skeleton::branch * &);
			void process_constant_int (mu::llvmc::ast::expression *);
            mu::llvmc::skeleton::type * process_type (mu::llvmc::ast::node *);
			mu::llvmc::global_processor & global_m;
			mu::llvmc::skeleton::module * module_m;
			mu::set <mu::llvmc::skeleton::global_value *> unnamed_globals;
			mu::set <mu::llvmc::skeleton::global_value *> named_globals;
			mu::set <mu::llvmc::ast::node *> current_expression_generation;
			mu::llvmc::ast::visitor * previous;
		};
        class function_processor : public mu::llvmc::ast::visitor
        {
        public:
            function_processor (mu::llvmc::module_processor & module_a, mu::llvmc::ast::function * node_a);
			~function_processor ();
			void process ();
            void process_value_call (mu::llvmc::ast::expression * expression_a);
            void process_marker (mu::llvmc::ast::expression * expression_a);
            void process_asm (mu::llvmc::ast::expression * expression_a);
			void process_binary_integer_instruction (mu::llvmc::ast::expression *, mu::vector <mu::llvmc::skeleton::node *> &, mu::vector <mu::llvmc::skeleton::value *> &, mu::llvmc::skeleton::branch *);
            mu::llvmc::skeleton::value * process_value (mu::llvmc::ast::node * node_a);
            void process_expression (mu::llvmc::ast::expression * node_a);
            void node (mu::llvmc::ast::node * node_a) override;
			void unit (mu::llvmc::ast::unit * node_a) override;
			void asm_c (mu::llvmc::ast::asm_c * asm_l) override;
			void join (mu::llvmc::ast::join * node_a) override;
			void loop (mu::llvmc::ast::loop * loop_a) override;
            void sequence (mu::llvmc::ast::sequence *) override;
			void expression (mu::llvmc::ast::expression * expression_a) override;
			void undefined (mu::llvmc::ast::undefined * node_a) override;
            void namespace_c (mu::llvmc::ast::namespace_c * node_a) override;
            void process_parameters ();
			void process_returns ();
            void process_results ();
			mu::llvmc::module_processor & module_m;
			mu::llvmc::skeleton::function * function_m;
			mu::llvmc::ast::function * node_m;
			mu::llvmc::ast::visitor * previous;
            mu::llvmc::skeleton::branch * previous_origin;
        };
		class branch_analyzer
		{
		public:
			branch_analyzer (mu::llvmc::skeleton::branch *, mu::core::error * &);
            mu::llvmc::skeleton::branch * add_branch (mu::llvmc::skeleton::branch *, mu::core::region const &);
			void new_set ();
			mu::llvmc::skeleton::branch * start;
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