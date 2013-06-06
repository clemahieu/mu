#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/node_result.hpp>
#include <mu/llvmc/instruction_type.hpp>
#include <mu/io/tokens.hpp>

namespace mu
{
    namespace io
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
            class node
            {
            public:
                virtual ~node ();
				mu::core::region region;
            };
            class value : public mu::llvmc::ast::node
            {
            public:
                value (mu::llvmc::skeleton::node * node_a);
                mu::llvmc::skeleton::node * node_m;
            };
            class result : public mu::llvmc::ast::node
            {
            public:
                result (mu::llvmc::ast::node * written_type_a);
                mu::llvmc::ast::node * written_type;
                mu::llvmc::ast::node * value;
            };
            class expression : public mu::llvmc::ast::node
            {
            };
            class loop_parameter : public mu::llvmc::ast::expression
            {
            public:
            };
            class unit : public mu::llvmc::ast::expression
            {                
            };
            class parameter : public mu::llvmc::ast::expression
            {
            public:
				parameter () = default;
                parameter (mu::string const & name_a, mu::llvmc::ast::node * type_a);
                mu::llvmc::ast::node * type;
				mu::string name;
            };
            class element : public mu::llvmc::ast::expression
            {
            public:
                element (mu::llvmc::ast::node * node_a, size_t index_a, size_t total_a, mu::string const & name_a, mu::core::region const & region_a);
                mu::llvmc::ast::node * node;
                size_t index;
                size_t total;
                mu::string name;
            };
			template <typename S, typename T, typename U, typename V, typename W>
			void for_each_argument (S arguments, size_t predicate_position, T argument_op, U predicate_op, V transition_op, W loop_op);
            class loop : public mu::llvmc::ast::expression
            {
            public:
				loop ();
                mu::vector <mu::llvmc::ast::node *> arguments;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::vector <mu::llvmc::ast::node *> roots;
				void set_argument_offset ();
				size_t argument_predicate_offset;
                mu::vector <mu::llvmc::ast::node *> results;
				void add_predicate_offset ();
				void add_branch_end ();
                mu::llvmc::ast::expression * as_expression (mu::llvmc::ast::node * node_a);
                template <typename T, typename U, typename V, typename W, typename X>
                void for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate);
				std::vector <size_t> predicate_offsets;
				std::vector <size_t> branch_ends;
            };
            class definite_expression : public mu::llvmc::ast::expression
            {
            public:
                definite_expression ();
                void set_predicate_position ();
                mu::vector <mu::llvmc::ast::node *> arguments;
                size_t predicate_position;
            };
            class set_expression : public mu::llvmc::ast::expression
            {
            public:
                mu::vector <mu::llvmc::ast::node *> items;
            };
            class if_expression : public mu::llvmc::ast::expression
            {
            public:
                mu::llvmc::ast::node * predicate;
                mu::vector <mu::llvmc::ast::node *> true_roots;
                mu::vector <mu::llvmc::ast::node *> false_roots;
            };
            class function : public mu::llvmc::ast::expression
            {
            public:
                mu::llvmc::availability::function * entry;
                mu::string name;
                mu::vector <mu::llvmc::ast::parameter *> parameters;
                mu::vector <mu::llvmc::ast::node *> results;
                std::vector <size_t> branch_ends;
                std::vector <size_t> predicate_offsets;
                mu::llvmc::ast::result * maybe_result (mu::llvmc::ast::node * node_a);
                mu::llvmc::ast::expression * maybe_expression (mu::llvmc::ast::node * node_a);
                template <typename T, typename U, typename V, typename W, typename X>
                void for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate);
                mu::vector <mu::llvmc::ast::node *> roots;
            };
            class type : public mu::llvmc::ast::node
            {
            };
            class integer_type : public mu::llvmc::ast::type
            {
            public:
                integer_type (mu::string const & bits_a);
                mu::string bits;
            };
            class pointer_type : public mu::llvmc::ast::type
            {
            public:
                pointer_type (mu::llvmc::ast::node * pointed_type_a);
                mu::llvmc::ast::node * pointed_type;
            };
            class module : public mu::llvmc::ast::node
            {
            public:
                module ();
                mu::vector <mu::llvmc::ast::node *> functions;
            };
            class constant_int : public mu::llvmc::ast::expression
            {
            public:
                constant_int (mu::string const & bits_a, mu::llvmc::ast::node * number_a);
                mu::string bits;
                mu::llvmc::ast::node * number;
            };
            class number : public mu::llvmc::ast::node
            {
            public:
                number (mu::string const & number_a);
                mu::string number_m;
            };
            class asm_c : public mu::llvmc::ast::node
            {
            public:
                asm_c () = default;
                asm_c (mu::llvmc::ast::node * type_a, mu::string const & text_a, mu::string const & constraints_a);
                mu::llvmc::ast::node * type;
                mu::string text;
                mu::string constraints;
            };
        }
    }
}