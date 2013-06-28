#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/instruction_type.hpp>
#include <mu/llvmc/predicates.hpp>
#include <mu/io/tokens.hpp>

namespace llvm
{
    class Constant;
    class Value;
}
namespace mu
{
    namespace llvmc
    {        
        class analyzer_function;
        namespace ast
        {
            class node;
        }
        namespace wrapper
        {
            class type;
        }
        namespace skeleton
        {
            class visitor;
            class node
            {
            public:
                virtual ~node ();
                virtual void visit (mu::llvmc::skeleton::visitor * visitor_a);
            };
            class type : public mu::llvmc::skeleton::node
            {
            public:
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                virtual bool operator == (mu::llvmc::skeleton::type const & other_a) const = 0;
                bool operator != (mu::llvmc::skeleton::type const & other_a) const;
                virtual bool is_unit_type () const;
            };
            class branch
            {
            public:
                branch (mu::llvmc::skeleton::branch * parent_a);
                mu::llvmc::skeleton::branch * most_specific (mu::llvmc::skeleton::branch * other_a);
                mu::llvmc::skeleton::branch * least_specific (mu::llvmc::skeleton::branch * other_a);
                mu::llvmc::skeleton::branch * parent;
            };
            class value : public mu::llvmc::skeleton::node
            {
            public:
                value (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                virtual mu::llvmc::skeleton::type * type () = 0;
                mu::llvmc::skeleton::branch * branch;
				mu::core::region region;
                llvm::Value * predicate;
                llvm::Value * generated;
            };
            class named : public mu::llvmc::skeleton::value
            {
            public:
                named (mu::core::region const & region_a, mu::llvmc::skeleton::value * value_a, mu::string const & name_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::value * value_m;
                mu::string name;
            };
            class parameter : public mu::llvmc::skeleton::value
            {
            public:
                parameter (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::string const & name_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
                mu::string name;
            };
            class constant : public mu::llvmc::skeleton::value
            {
            public:
                constant (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
            };
            class constant_integer : public mu::llvmc::skeleton::constant
            {
            public:
                constant_integer (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, size_t bits_a, uint64_t value_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
                uint64_t value_m;
            };
            class constant_aggregate_zero : public mu::llvmc::skeleton::constant
            {
            public:
                constant_aggregate_zero (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
            };
            class constant_pointer_null : public mu::llvmc::skeleton::constant
            {
            public:
                constant_pointer_null (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
            };
            class array_type : public mu::llvmc::skeleton::type
            {
            public:
                array_type (mu::llvmc::skeleton::type * element_a, size_t size_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
                mu::llvmc::skeleton::type * element;
                size_t size;
            };
			class constant_array : public mu::llvmc::skeleton::constant
			{
			public:
				constant_array (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::array_type * type_a, mu::vector <mu::llvmc::skeleton::constant *> const & initializer_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::array_type * type_m;
				mu::vector <mu::llvmc::skeleton::constant *> initializer;
			};
            class instruction : public mu::llvmc::skeleton::value
            {
            public:
                instruction (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_position_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * binary_integer_type ();
                mu::llvmc::skeleton::type * get_type ();
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::instruction_type marker ();
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                size_t predicate_position;
                mu::llvmc::skeleton::type * type_m;
            };
            class join : public mu::llvmc::skeleton::node
            {
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
            };
			class predicate : public mu::llvmc::skeleton::node
			{
			public:
				predicate (mu::llvmc::predicates type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
				mu::llvmc::predicates type;
			};
            class marker : public mu::llvmc::skeleton::node
            {
            public:
                marker (mu::llvmc::instruction_type type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::instruction_type type;
            };
            class integer_type : public mu::llvmc::skeleton::type
            {
            public:
                integer_type (size_t bits_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
                size_t bits;
            };
            class struct_type : public mu::llvmc::skeleton::type
            {
            public:
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::vector <mu::llvmc::skeleton::type *> elements;
            };
            class unit_type : public mu::llvmc::skeleton::type
            {
            public:
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
                bool is_unit_type () const override;
            };
            class result : public mu::llvmc::skeleton::node
            {
            public:
                result (mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * value_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type;
                mu::llvmc::skeleton::value * value;
            };
            class function;
            class function_type : public mu::llvmc::skeleton::type
            {
            public:
                function_type (mu::llvmc::skeleton::function * function_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
                mu::llvmc::skeleton::function * function;
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
            class pointer_type : public mu::llvmc::skeleton::type
            {
            public:
                pointer_type (mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
                mu::llvmc::skeleton::type * pointed_type;
            };
            class function : public mu::llvmc::skeleton::constant
            {
            public:
                function (mu::core::region const & region_a, mu::llvmc::skeleton::branch * global_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                size_t branch_size (size_t index) const;
                mu::llvmc::skeleton::function_return_type get_return_type ();
                mu::llvmc::skeleton::function_type type_m;
                mu::llvmc::skeleton::pointer_type pointer_type_m;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::branch * entry;
                mu::vector <mu::llvmc::skeleton::parameter *> parameters;
                mu::vector <mu::llvmc::skeleton::node *> results;
                std::vector <size_t> branch_ends;
                std::vector <size_t> predicate_offsets;
				size_t predicate_offset;
				void add_branch_end ();
				void add_predicate_offset ();
				void set_predicate_offset ();
                template <typename T>
                void for_each_branch (T branch_op);
                mu::llvmc::skeleton::result * as_result (mu::llvmc::skeleton::node * node_a);
                mu::llvmc::skeleton::value * as_value (mu::llvmc::skeleton::node * node_a);
                static void empty_node (mu::llvmc::skeleton::node *, size_t);
                static bool empty_loop_predicate ();
                template <typename T = decltype (empty_node), typename U = decltype (empty_node), typename V = decltype (empty_node), typename W = decltype (empty_node), typename X = decltype (empty_loop_predicate)>
                void for_each_results (T result_op = empty_node, U predicate_op = empty_node, V transition_op = empty_node, W branch_op = empty_node, X loop_predicate = empty_loop_predicate);
            };
            class switch_element;
            class switch_i
            {
            public:
                switch_i (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a);
                mu::llvmc::skeleton::branch * branch;
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                mu::vector <mu::llvmc::skeleton::switch_element *> elements;
            };
            class switch_element : public mu::llvmc::skeleton::value
            {
            public:
                switch_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::switch_i * source_a, mu::llvmc::skeleton::constant_integer * value_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::switch_i * source;
                mu::llvmc::skeleton::constant_integer * value_m;
            };
            class call_element;
            class function_call
            {
            public:
                function_call (mu::llvmc::skeleton::function * target_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_offset_a);
                mu::llvmc::skeleton::function * target;
                mu::llvmc::skeleton::branch * branch;
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                mu::vector <mu::llvmc::skeleton::call_element *> elements;
                size_t predicate_offset;
            };
            class call_element : public mu::llvmc::skeleton::value
            {
            public:
                call_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::function_call * source;
            };
            class call_element_value : public mu::llvmc::skeleton::call_element
            {
            public:
                call_element_value (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, size_t index_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                size_t index;
            };
            class call_element_unit : public mu::llvmc::skeleton::call_element
            {
            public:
                call_element_unit (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
            };
			class loop;
			class loop_element : public mu::llvmc::skeleton::value
			{
			public:
				loop_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::loop * source_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
				mu::llvmc::skeleton::loop * source;
			};
			class loop_parameter : public mu::llvmc::skeleton::value
			{
			public:
				loop_parameter (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
				mu::llvmc::skeleton::type * type () override;
				mu::llvmc::skeleton::type * type_m;
			};
			class loop
			{
			public:
				loop ();
				mu::llvmc::skeleton::branch * loop_entry_branch;
				mu::vector <mu::llvmc::skeleton::node *> arguments;
				size_t argument_predicate_offset;
				void set_argument_predicate_offset ();
				mu::vector <mu::llvmc::skeleton::loop_parameter *> parameters;
				mu::vector <mu::llvmc::skeleton::value *> results;
				std::vector <size_t> predicate_offsets;
				std::vector <size_t> branch_ends;
				mu::vector <mu::llvmc::skeleton::loop_element *> elements;
                static void empty_node (mu::llvmc::skeleton::node *, size_t);
                static bool empty_loop_predicate ();
                template <typename T = decltype (empty_node), typename U = decltype (empty_node), typename V = decltype (empty_node), typename W = decltype (empty_node), typename X = decltype (empty_loop_predicate)>
                void for_each_results (T result_op = empty_node, U predicate_op = empty_node, V transition_op = empty_node, W branch_op = empty_node, X loop_predicate = empty_loop_predicate);
			};
			class loop_element_value : public mu::llvmc::skeleton::loop_element
			{
			public:
				loop_element_value (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::loop * source_a, size_t index_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
				mu::llvmc::skeleton::type * type () override;
				size_t index;
			};
			class loop_element_unit : public mu::llvmc::skeleton::loop_element
			{
			public:
				loop_element_unit (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::loop * source_a, size_t index_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
				mu::llvmc::skeleton::type * type () override;
				size_t index;
			};
            class unit_value : public mu::llvmc::skeleton::value
            {
            public:
                unit_value (mu::llvmc::skeleton::branch * branch_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
            };
            class join_value : public mu::llvmc::skeleton::value
            {
            public:
                join_value (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::value *> const & arguments_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::vector <mu::llvmc::skeleton::value *> arguments;
            };
			class global_variable : public mu::llvmc::skeleton::constant
			{
			public:
				global_variable (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::constant * initializer_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
				mu::llvmc::skeleton::type * type_m;
				mu::llvmc::skeleton::constant * initializer;
			};			
            class module
            {
            public:
                module ();
                mu::map <mu::string, mu::llvmc::skeleton::constant *> globals;
                mu::llvmc::skeleton::branch * global;
                mu::llvmc::skeleton::unit_value the_unit_value;
            };
            class number
            {
            public:
                number (uint64_t value_a);
                uint64_t value;
            };
            class asm_c : public mu::llvmc::skeleton::node
            {
            public:
                asm_c (mu::llvmc::skeleton::type * type_a, mu::string const & text_a, mu::string const & constraint_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type_m;
                mu::string text;
                mu::string constraint;
            };
			class inline_asm : public mu::llvmc::skeleton::value
			{
			public:
				inline_asm (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_position_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
				mu::vector <mu::llvmc::skeleton::node *> arguments;
				size_t predicate_position;
			};
            class identity : public mu::llvmc::skeleton::node
            {
            public:
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
            };
            class identity_call;
            class identity_element : public mu::llvmc::skeleton::value
            {
            public:
                identity_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::identity_call * source_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::identity_call * source;
            };
            class identity_element_value : public mu::llvmc::skeleton::identity_element
            {
            public:
                identity_element_value (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::identity_call * source_a, size_t index_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                size_t index;
            };
            class identity_element_unit : public mu::llvmc::skeleton::identity_element
            {
            public:
                identity_element_unit (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::identity_call * source_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
            };
            class identity_call
            {
            public:
                identity_call (mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_offset_a);
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                size_t predicate_offset;
                mu::vector <mu::llvmc::skeleton::identity_element *> elements;
            };
            class visitor
            {
            public:
                void unexpected (mu::llvmc::skeleton::node * node_a);
                virtual void node (mu::llvmc::skeleton::node * node_a);
                virtual void array_type (mu::llvmc::skeleton::array_type * node_a);
                virtual void inline_asm (mu::llvmc::skeleton::inline_asm * node_a);
                virtual void join_value (mu::llvmc::skeleton::join_value * node_a);
                virtual void unit_value (mu::llvmc::skeleton::unit_value * node_a);
                virtual void instruction (mu::llvmc::skeleton::instruction * node_a);
                virtual void struct_type (mu::llvmc::skeleton::struct_type * node_a);
                virtual void call_element (mu::llvmc::skeleton::call_element * node_a);
                virtual void integer_type (mu::llvmc::skeleton::integer_type * node_a);
                virtual void loop_element (mu::llvmc::skeleton::loop_element * node_a);
                virtual void pointer_type (mu::llvmc::skeleton::pointer_type * node_a);
                virtual void function_type (mu::llvmc::skeleton::function_type * node_a);
                virtual void constant_array (mu::llvmc::skeleton::constant_array * node_a);
                virtual void loop_parameter (mu::llvmc::skeleton::loop_parameter * node_a);
                virtual void switch_element (mu::llvmc::skeleton::switch_element * node_a);
                virtual void global_variable (mu::llvmc::skeleton::global_variable * node_a);
                virtual void constant_integer (mu::llvmc::skeleton::constant_integer * node_a);
                virtual void constant_pointer_null (mu::llvmc::skeleton::constant_pointer_null * node_a);
                virtual void identity_element_value (mu::llvmc::skeleton::identity_element_value * node_a);
                virtual void constant_aggregate_zero (mu::llvmc::skeleton::constant_aggregate_zero * node_a);
                virtual void join (mu::llvmc::skeleton::join * node_a);
                virtual void type (mu::llvmc::skeleton::type * node_a);
                virtual void asm_c (mu::llvmc::skeleton::asm_c * node_a);
                virtual void named (mu::llvmc::skeleton::named * node_a);
                virtual void value (mu::llvmc::skeleton::value * node_a);
                virtual void marker (mu::llvmc::skeleton::marker * node_a);
                virtual void result (mu::llvmc::skeleton::result * node_a);
                virtual void constant (mu::llvmc::skeleton::constant * node_a);
                virtual void function (mu::llvmc::skeleton::function * node_a);
                virtual void identity (mu::llvmc::skeleton::identity * node_a);
                virtual void parameter (mu::llvmc::skeleton::parameter * node_a);
                virtual void predicate (mu::llvmc::skeleton::predicate * node_a);
                virtual void unit_type (mu::llvmc::skeleton::unit_type * node_a);
                virtual void identity_element (mu::llvmc::skeleton::identity_element * node_a);
                virtual void call_element_unit (mu::llvmc::skeleton::call_element_unit * node_a);
                virtual void loop_element_value (mu::llvmc::skeleton::loop_element_value * node_a);
                virtual void loop_element_unit (mu::llvmc::skeleton::loop_element_unit * node_a);
                virtual void call_element_value (mu::llvmc::skeleton::call_element_value * node_a);
                virtual void identity_element_unit (mu::llvmc::skeleton::identity_element_unit * node_a);
            };
            extern mu::llvmc::skeleton::integer_type integer_1_type;
            extern mu::llvmc::skeleton::integer_type integer_8_type;
            extern mu::llvmc::skeleton::unit_type the_unit_type;
        }
    }
}