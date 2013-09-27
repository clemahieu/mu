#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/instruction_type.hpp>
#include <mu/llvmc/predicates.hpp>
#include <mu/io/tokens.hpp>

#include <llvm/DebugInfo.h>

namespace llvm
{
    class Constant;
    class Value;
}
namespace mu
{
    namespace llvmc
    {
        class template_context;
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
			class namespace_visitor;
            class node
            {
            public:
                virtual ~node ();
                virtual void visit (mu::llvmc::skeleton::visitor * visitor_a);
				virtual void named (mu::llvmc::skeleton::namespace_visitor * naming_a);
            };
			class namespace_container
			{
			public:
				virtual mu::llvmc::skeleton::node * operator [] (mu::string const & name_a) = 0;
			};
            class type : public mu::llvmc::skeleton::node
            {
            public:
                type ();
                llvm::Type * generated;
                llvm::DIType debug;
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
			class predicate : public mu::llvmc::skeleton::node
			{
			public:
				predicate (mu::llvmc::predicates type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
				mu::llvmc::predicates type;
			};
            class icmp : public mu::llvmc::skeleton::value
            {
            public:
                icmp (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::predicate * predicate_a, mu::llvmc::skeleton::value * left_a, mu::llvmc::skeleton::value * right_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
                mu::llvmc::skeleton::predicate * predicate_m;
                mu::llvmc::skeleton::value * left;
                mu::llvmc::skeleton::value * right;
                mu::vector <mu::llvmc::skeleton::node *> predicates;
            };
            class store : public mu::llvmc::skeleton::value
            {
            public:
                store (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::llvmc::skeleton::value * source_a, mu::llvmc::skeleton::value * destination_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
                mu::llvmc::skeleton::value * source;
                mu::llvmc::skeleton::value * destination;
                mu::vector <mu::llvmc::skeleton::node *> predicates;
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
                bool operator == (mu::llvmc::skeleton::type const & other_a) const override;
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
            class global_value : public mu::llvmc::skeleton::constant
            {
            public:
                global_value (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::string name;
            };
            class function : public mu::llvmc::skeleton::global_value
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
                llvm::DISubprogram debug;
            };
            class switch_element;
            class switch_i
            {
            public:
                switch_i (mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, mu::llvmc::skeleton::unit_type * type_a);
                mu::llvmc::skeleton::branch * branch;
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                mu::vector <mu::llvmc::skeleton::switch_element *> elements;
                mu::llvmc::skeleton::unit_type * type_m;
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
                function_call (mu::llvmc::skeleton::function * target_a, mu::llvmc::skeleton::branch * branch_a, mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_offset_a, mu::llvmc::skeleton::type * type_a);
                mu::llvmc::skeleton::function * target;
                mu::llvmc::skeleton::branch * branch;
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                mu::vector <mu::llvmc::skeleton::call_element *> elements;
                size_t predicate_offset;
                mu::llvmc::skeleton::type * type_m;
            };
            class call_element : public mu::llvmc::skeleton::value
            {
            public:
                call_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::function_call * source_a, mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::function_call * source;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
            };
			class loop;
			class loop_element : public mu::llvmc::skeleton::value
			{
			public:
				loop_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::loop * source_a, mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
				mu::llvmc::skeleton::loop * source;
                mu::llvmc::skeleton::type * type_m;
			};
			class loop_parameter : public mu::llvmc::skeleton::value
			{
			public:
				loop_parameter (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a, mu::string const & name_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
				mu::llvmc::skeleton::type * type () override;
				mu::llvmc::skeleton::type * type_m;
                mu::string name;
			};
			class loop
			{
			public:
				loop (mu::llvmc::skeleton::type * type_a);
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
                mu::llvmc::skeleton::type * type_m;
			};
            class unit_value : public mu::llvmc::skeleton::value
            {
            public:
                unit_value (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
            };
            class join_element;
            class join_branch
            {
            public:
                join_branch ();
                mu::vector <mu::llvmc::skeleton::value *> arguments;
                mu::vector <mu::llvmc::skeleton::value *> predicates;
                llvm::Value * predicate;
            };
            class join_value
            {
            public:
                mu::llvmc::skeleton::join_branch & add_branch ();
                mu::vector <mu::llvmc::skeleton::join_branch> branches;
                mu::vector <mu::llvmc::skeleton::join_element *> elements;
            };
            class join_element : public mu::llvmc::skeleton::value
            {
            public:
                join_element (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::join_value * source_a, mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::join_value * source;
                mu::llvmc::skeleton::type * type_m;
            };
			class global_variable : public mu::llvmc::skeleton::global_value
			{
			public:
				global_variable (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::constant * initializer_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
				mu::llvmc::skeleton::type * type_m;
				mu::llvmc::skeleton::constant * initializer;
                llvm::DIGlobalVariable debug;
			};			
            class module : public mu::llvmc::skeleton::node, public mu::llvmc::skeleton::namespace_container
            {
            public:
                module ();
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
				void named (mu::llvmc::skeleton::namespace_visitor * naming_a) override;
				mu::llvmc::skeleton::node * operator [] (mu::string const & method_a) override;
				mu::map <mu::string, mu::llvmc::skeleton::node *> names;
                mu::vector <mu::llvmc::skeleton::value *> globals;
                mu::llvmc::skeleton::branch * global;
				mu::llvmc::skeleton::function * entry;
                mu::llvmc::skeleton::integer_type integer_1_type;
                mu::llvmc::skeleton::integer_type integer_8_type;
                mu::llvmc::skeleton::unit_type the_unit_type;
                mu::llvmc::skeleton::unit_value the_unit_value;
            };
            class number
            {
            public:
                number (uint64_t value_a);
                uint64_t value;
            };
			class template_c : public mu::llvmc::skeleton::node
			{
			public:
                template_c (mu::llvmc::template_context * base_a);
                mu::llvmc::template_context * base;
				mu::vector <mu::llvmc::ast::node *> body;
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
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
                identity_element (mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::identity_call * source_a, mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::identity_call * source;
                mu::llvmc::skeleton::type * type () override;
                mu::llvmc::skeleton::type * type_m;
            };
            class identity_call
            {
            public:
                identity_call (mu::vector <mu::llvmc::skeleton::node *> const & arguments_a, size_t predicate_offset_a, mu::llvmc::skeleton::type * type_a);
                mu::vector <mu::llvmc::skeleton::node *> arguments;
                size_t predicate_offset;
                mu::vector <mu::llvmc::skeleton::identity_element *> elements;
                mu::llvmc::skeleton::type * type_m;
            };
			class undefined : public mu::llvmc::skeleton::value
			{
			public:
				undefined (mu::core::region const & region_a, mu::llvmc::skeleton::branch * branch_a, mu::llvmc::skeleton::type * type_a);
                void visit (mu::llvmc::skeleton::visitor * visitor_a) override;
                mu::llvmc::skeleton::type * type () override;
				mu::llvmc::skeleton::type * type_m;
			};
            class visitor
            {
            public:
                void unexpected (mu::llvmc::skeleton::node * node_a);
                virtual void node (mu::llvmc::skeleton::node * node_a);
                virtual void array_type (mu::llvmc::skeleton::array_type * node_a);
                virtual void inline_asm (mu::llvmc::skeleton::inline_asm * node_a);
                virtual void join_element (mu::llvmc::skeleton::join_element * node_a);
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
                virtual void constant_aggregate_zero (mu::llvmc::skeleton::constant_aggregate_zero * node_a);
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
                virtual void icmp (mu::llvmc::skeleton::icmp * node_a);
                virtual void store (mu::llvmc::skeleton::store * node_a);
				virtual void undefined (mu::llvmc::skeleton::undefined * node_a);
                virtual void template_c (mu::llvmc::skeleton::template_c * node_a);
                virtual void global_value (mu::llvmc::skeleton::global_value * node_a);
				virtual void module (mu::llvmc::skeleton::module * node_a);
            };
			class namespace_visitor
			{
			public:
				virtual void named (mu::llvmc::skeleton::namespace_container * namespace_a) = 0;
				virtual void unnamed () = 0;
			};
        }
    }
}