#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/node_result.hpp>
#include <mu/llvmc/instruction_type.hpp>
#include <mu/io/tokens.hpp>

namespace mu
{
    namespace iou
    {
        template <typename T>
        class stream;
        class token;
    }
    namespace llvmc
    {
        namespace availability
        {
            class node;
            class function;
            class module;
        }
        namespace skeleton
        {
            class node;
        }
        namespace ast
        {
            class visitor;
            class node
            {
            public:
                virtual ~node ();
                virtual void visit (mu::llvmc::ast::visitor * visitor_a);
				mu::core::region region;
            };
            class value : public mu::llvmc::ast::node
            {
            public:
                value (mu::llvmc::skeleton::node * node_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::skeleton::node * node_m;
            };
            class result : public mu::llvmc::ast::node
            {
            public:
                result (mu::llvmc::ast::node * written_type_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * written_type;
                mu::llvmc::ast::node * value;
            };
            class loop_parameter : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
            };
            class unit : public mu::llvmc::ast::node
            {
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
            };
            class parameter : public mu::llvmc::ast::node
            {
            public:
				parameter () = default;
                parameter (mu::string const & name_a, mu::llvmc::ast::node * type_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
				mu::string name;
            };
            class element : public mu::llvmc::ast::node
            {
            public:
                element (mu::llvmc::ast::node * node_a, size_t index_a, size_t total_a, mu::string const & name_a, mu::core::region const & region_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * node;
                size_t index;
                size_t total;
                mu::string name;
            };
			template <typename S, typename T, typename U, typename V, typename W>
			void for_each_argument (S arguments, size_t predicate_position, T argument_op, U predicate_op, V transition_op, W loop_op);
            class loop : public mu::llvmc::ast::node
            {
            public:
				loop ();
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::vector <mu::llvmc::ast::node *> arguments;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::vector <mu::llvmc::ast::node *> roots;
				void set_argument_offset ();
				size_t argument_predicate_offset;
                mu::vector <mu::llvmc::ast::node *> results;
				void add_predicate_offset ();
				void add_branch_end ();
                template <typename T, typename U, typename V, typename W, typename X>
                void for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate);
				std::vector <size_t> predicate_offsets;
				std::vector <size_t> branch_ends;
            };
            class definite_expression : public mu::llvmc::ast::node
            {
            public:
                definite_expression ();
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                void set_predicate_position ();
                mu::vector <mu::llvmc::ast::node *> arguments;
                size_t predicate_position;
            };
            class set_expression : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::vector <mu::llvmc::ast::node *> items;
            };
            class if_expression : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * predicate;
                mu::vector <mu::llvmc::ast::node *> true_roots;
                mu::vector <mu::llvmc::ast::node *> false_roots;
            };
            class function : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::availability::function * entry;
                mu::vector <mu::llvmc::ast::parameter *> parameters;
                mu::vector <mu::llvmc::ast::node *> results;
                std::vector <size_t> branch_ends;
                std::vector <size_t> predicate_offsets;
                template <typename T, typename U, typename V, typename W, typename X>
                void for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate);
                mu::vector <mu::llvmc::ast::node *> roots;
            };
            class integer_type : public mu::llvmc::ast::node
            {
            public:
                integer_type (mu::string const & bits_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::string bits;
            };
            class pointer_type : public mu::llvmc::ast::node
            {
            public:
                pointer_type (mu::llvmc::ast::node * pointed_type_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * pointed_type;
            };
            class array_type : public mu::llvmc::ast::node
            {
            public:
                array_type () = default;
                array_type (mu::llvmc::ast::node * element_type_a, mu::llvmc::ast::node * size_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * element_type;
                mu::llvmc::ast::node * size;
            };
            class unit_type : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
            };
            class module : public mu::llvmc::ast::node
            {
            public:
                module ();
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::map <mu::string, mu::llvmc::ast::node *> globals;
            };
            class constant_int : public mu::llvmc::ast::node
            {
            public:
                constant_int (mu::string const & bits_a, mu::llvmc::ast::node * number_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::string bits;
                mu::llvmc::ast::node * number;
            };
            class constant_array : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
                mu::vector <mu::llvmc::ast::node *> initializer;
            };
            class constant_pointer_null : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
            };
            class number : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                number (mu::string const & number_a);
                mu::string number_m;
            };
            class asm_c : public mu::llvmc::ast::node
            {
            public:
                asm_c () = default;
                asm_c (mu::llvmc::ast::node * type_a, mu::string const & text_a, mu::string const & constraints_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
                mu::string text;
                mu::string constraints;
            };
            class global_variable : public mu::llvmc::ast::node
            {
            public:
                global_variable () = default;
                global_variable (mu::llvmc::ast::node * initializer_a);
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * initializer;
            };
            class join_branch
            {
            public:
                mu::vector <mu::llvmc::ast::node *> arguments;
                mu::vector <mu::llvmc::ast::node *> predicates;
            };
            class join : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::vector <mu::llvmc::ast::join_branch> branches;
                mu::llvmc::ast::join_branch & add_branch ();
            };
            class struct_type : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::vector <mu::llvmc::ast::node *> elements;
            };
            class undefined_value : public mu::llvmc::ast::node
            {
            public:
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
            };
            class visitor
            {
            public:
                void unexpected (mu::llvmc::ast::node * node_a);
                virtual void node (mu::llvmc::ast::node * node_a);
                virtual void array_type (mu::llvmc::ast::array_type * node_a);
                virtual void constant_int (mu::llvmc::ast::constant_int * node_a);
                virtual void integer_type (mu::llvmc::ast::integer_type * node_a);
                virtual void pointer_type (mu::llvmc::ast::pointer_type * node_a);
                virtual void constant_array (mu::llvmc::ast::constant_array * node_a);
                virtual void set_expression (mu::llvmc::ast::set_expression * node_a);
                virtual void global_variable (mu::llvmc::ast::global_variable * node_a);
                virtual void definite_expression (mu::llvmc::ast::definite_expression * node_a);
                virtual void constant_pointer_null (mu::llvmc::ast::constant_pointer_null * node_a);
                virtual void join (mu::llvmc::ast::join * node_a);
                virtual void loop (mu::llvmc::ast::loop * node_a);
                virtual void unit (mu::llvmc::ast::unit * node_a);
                virtual void asm_c (mu::llvmc::ast::asm_c * node_a);
                virtual void value (mu::llvmc::ast::value * node_a);
                virtual void module (mu::llvmc::ast::module * node_a);
                virtual void number (mu::llvmc::ast::number * node_a);
                virtual void result (mu::llvmc::ast::result * node_a);
                virtual void element (mu::llvmc::ast::element * node_a);
                virtual void function (mu::llvmc::ast::function * node_a);
                virtual void unit_type (mu::llvmc::ast::unit_type * node_a);
                virtual void loop_parameter (mu::llvmc::ast::loop_parameter * node_a);
                virtual void parameter (mu::llvmc::ast::parameter * node_a);
                virtual void struct_type (mu::llvmc::ast::struct_type * node_a);
                virtual void undefined_value (mu::llvmc::ast::undefined_value * node_a);
            };
        }
    }
}