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
        namespace skeleton
        {
            class node;
        }
		class template_context;
        class clone_context
        {
        public:
            clone_context (mu::llvmc::template_context * template_a);
            mu::llvmc::template_context * template_m;
            mu::map <mu::llvmc::ast::node *, mu::llvmc::ast::node *> generated;
        };
        namespace ast
        {
            class visitor;
			class namespace_visitor;
            class node
            {
            public:
				node (mu::llvmc::template_context * template_a = nullptr);
				node (mu::llvmc::ast::node const & other_a) = delete;
                node (mu::llvmc::ast::node const & other_a, mu::llvmc::clone_context & context_a);
                virtual ~node ();
				mu::llvmc::ast::node * clone (mu::llvmc::clone_context & context_a);
                virtual void visit (mu::llvmc::ast::visitor * visitor_a);
                virtual bool is_sequenced () const;
				mu::llvmc::template_context * template_m;
				mu::core::region region;
				mu::vector <mu::llvmc::skeleton::node *> generated;
				bool assigned;
			private:
				virtual mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a);
            };
            class value : public mu::llvmc::ast::node
            {
            public:
				value (mu::llvmc::ast::value const & other_a, mu::llvmc::clone_context & context_a);
                value (mu::llvmc::skeleton::node * node_a, mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::skeleton::node * node_m;
            };
            class result : public mu::llvmc::ast::node
            {
            public:
                result (mu::llvmc::template_context * template_a = nullptr);
				result (mu::llvmc::ast::result const & other_a, mu::llvmc::clone_context & context_a);
                result (mu::llvmc::ast::node * written_type_a, mu::llvmc::ast::node * value_a, mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * written_type;
                mu::llvmc::ast::node * value;
            };
            class loop_parameter : public mu::llvmc::ast::node
            {
            public:
				loop_parameter (mu::llvmc::ast::loop_parameter const & other_a);
				loop_parameter (mu::string const & name_a, mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
				mu::string name;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
            };
            class unit : public mu::llvmc::ast::node
            {
			public:
				unit (mu::llvmc::template_context * template_a = nullptr);
				unit (mu::llvmc::ast::unit const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
            };
            class parameter : public mu::llvmc::ast::node
            {
            public:
				parameter (mu::llvmc::template_context * template_a = nullptr);
				parameter (mu::llvmc::ast::parameter const & other_a, mu::llvmc::clone_context & context_a);
                parameter (mu::string const & name_a, mu::llvmc::ast::node * type_a, mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
				mu::string name;
            };
            class element : public mu::llvmc::ast::node
            {
            public:
                element (mu::llvmc::ast::node * node_a, size_t index_a, size_t total_a, mu::string const & name_a, mu::core::region const & region_a, mu::llvmc::template_context * template_a = nullptr);
				element (mu::llvmc::ast::element const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * node_m;
                size_t index;
                size_t total;
                mu::string name;
            };
            class loop : public mu::llvmc::ast::node
            {
            public:
				loop (mu::llvmc::template_context * template_a = nullptr);
				loop (mu::llvmc::ast::loop const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::vector <mu::llvmc::ast::node *> arguments;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::vector <mu::llvmc::ast::node *> roots;
                mu::vector <mu::llvmc::ast::node *> results;
				void add_predicate_offset ();
				void add_branch_end ();
                template <typename T, typename U, typename V, typename W, typename X>
                void for_each_results (T result_op, U predicate_op, V transition_op, W branch_op, X loop_predicate);
				std::vector <size_t> predicate_offsets;
				std::vector <size_t> branch_ends;
            };
            class expression : public mu::llvmc::ast::node
            {
            public:
                expression (mu::llvmc::template_context * template_a = nullptr);
                expression (std::initializer_list <mu::llvmc::ast::node *> arguments, mu::llvmc::template_context * template_a = nullptr);
				expression (mu::llvmc::ast::expression const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::vector <mu::llvmc::ast::node *> arguments;
            };
            class function_branch
            {
            public:
                function_branch () = default;
                function_branch (std::initializer_list <mu::llvmc::ast::node *> const &);
                function_branch (mu::llvmc::ast::function_branch const &, mu::llvmc::clone_context &);
                mu::vector <mu::llvmc::ast::node *> nodes;
            };
            class function_result
            {
            public:
                function_result () = default;
                function_result (std::initializer_list <mu::llvmc::ast::function_branch> const &);
                function_result (mu::llvmc::ast::function_result const &, mu::llvmc::clone_context &);
                mu::llvmc::ast::function_branch & add_branch ();
                mu::vector <mu::llvmc::ast::function_branch> branches;
            };
            class function : public mu::llvmc::ast::node
            {
            public:
				function (mu::llvmc::template_context * template_a = nullptr);
				function (mu::llvmc::ast::function const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::llvmc::ast::function_result results;
                mu::vector <mu::llvmc::ast::node *> roots;
            };
            class integer_type : public mu::llvmc::ast::node
            {
            public:
				integer_type (mu::llvmc::ast::integer_type const & other_a);
                integer_type (mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
				mu::llvmc::ast::node * bits;
            };
            class pointer_type : public mu::llvmc::ast::node
            {
            public:
                pointer_type (mu::llvmc::template_context * template_a = nullptr);
				pointer_type (mu::llvmc::ast::pointer_type const & other_a, mu::llvmc::clone_context & context_a);
                pointer_type (mu::llvmc::ast::node * pointed_type_a, mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * pointed_type;
            };
            class fixed_array_type : public mu::llvmc::ast::node
            {
            public:
                fixed_array_type (mu::llvmc::template_context * template_a = nullptr);
				fixed_array_type (mu::llvmc::ast::fixed_array_type const & other_a, mu::llvmc::clone_context & context_a);
                fixed_array_type (mu::llvmc::ast::node * element_type_a, mu::llvmc::ast::node * size_a, mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * element_type;
                mu::llvmc::ast::node * size;
            };
            class array_type : public mu::llvmc::ast::node
            {
            public:
                array_type (mu::llvmc::template_context * template_a = nullptr);
                array_type (mu::llvmc::ast::array_type const & other_a, mu::llvmc::clone_context & context_a);
                array_type (mu::llvmc::ast::node * element_type_a, mu::llvmc::template_context * template_a = nullptr);
                mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * element_type;
            };
            class unit_type : public mu::llvmc::ast::node
            {
            public:
				unit_type (mu::llvmc::template_context * template_a = nullptr);
				unit_type (mu::llvmc::ast::unit_type const & other_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
            };
            class module : public mu::llvmc::ast::node
            {
            public:
                module (mu::llvmc::template_context * template_a = nullptr);
				module (mu::llvmc::ast::module const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::vector <mu::llvmc::ast::node *> globals;
                mu::map <mu::string, mu::llvmc::ast::node *> names;
				void dump ();
            };
            class constant_int : public mu::llvmc::ast::node
            {
            public:
				constant_int (mu::llvmc::ast::constant_int const & other_a, mu::llvmc::clone_context & context_a);
                constant_int (mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
            };
            class constant_array : public mu::llvmc::ast::node
            {
            public:
				constant_array (mu::llvmc::template_context * template_a = nullptr);
				constant_array (mu::llvmc::ast::constant_array const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
                mu::vector <mu::llvmc::ast::node *> initializer;
            };
            class constant_pointer_null : public mu::llvmc::ast::node
            {
            public:
				constant_pointer_null (mu::llvmc::template_context * template_a = nullptr);
				constant_pointer_null (mu::llvmc::ast::constant_pointer_null const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
            };
            class number : public mu::llvmc::ast::node
            {
            public:
                number (mu::string const & number_a, mu::llvmc::template_context * context_a = nullptr);
                number (mu::llvmc::ast::number const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::string number_m;
            };
            class asm_c : public mu::llvmc::ast::node
            {
            public:
                asm_c (mu::llvmc::template_context * template_a = nullptr);
				asm_c (mu::llvmc::ast::asm_c const & other_a, mu::llvmc::clone_context & context_a);
                asm_c (mu::llvmc::ast::node * type_a, mu::string const & text_a, mu::string const & constraints_a, mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
                mu::string text;
                mu::string constraints;
            };
            class global_variable : public mu::llvmc::ast::node
            {
            public:
                global_variable (mu::llvmc::template_context * template_a = nullptr);
				global_variable (mu::llvmc::ast::global_variable const & other_a, mu::llvmc::clone_context & context_a);
                global_variable (mu::llvmc::ast::node * initializer_a, mu::llvmc::template_context * template_a = nullptr);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
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
				join (mu::llvmc::template_context * context_a = nullptr);
				join (mu::llvmc::ast::join const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::vector <mu::llvmc::ast::join_branch> branches;
                mu::llvmc::ast::join_branch & add_branch ();
            };
            class struct_type : public mu::llvmc::ast::node
            {
            public:
				struct_type (mu::llvmc::template_context * context_a = nullptr);
				struct_type (mu::llvmc::ast::struct_type const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
				mu::map <mu::string, size_t> names;
                mu::vector <mu::llvmc::ast::node *> elements;
            };
            class undefined : public mu::llvmc::ast::node
            {
            public:
				undefined (mu::llvmc::template_context * context_a = nullptr);
				undefined (mu::llvmc::ast::undefined const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * type;
            };
			class template_parameter : public mu::llvmc::ast::node
			{
			public:
				template_parameter (mu::string const & name_a, mu::llvmc::template_context * template_a = nullptr);
				template_parameter (mu::llvmc::ast::template_parameter const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
				size_t argument;
				mu::string name;
			};
			class template_c : public mu::llvmc::ast::node
			{
			public:
				template_c (mu::llvmc::template_context * base_a, mu::llvmc::template_context * context_a = nullptr);
				template_c (mu::llvmc::ast::template_c const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::template_context * base;
                mu::vector <mu::llvmc::ast::node *> parameters;
				mu::vector <mu::llvmc::ast::node *> body;
			};
            class entry : public mu::llvmc::ast::node
            {
            public:
                entry (mu::llvmc::template_context * context_a = nullptr);
				entry (mu::llvmc::ast::entry const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
                void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::llvmc::ast::node * function;
            };
			class set : public mu::llvmc::ast::node
			{
			public:
				set (mu::llvmc::template_context * context_a = nullptr);
				set (mu::llvmc::ast::set const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
				void visit (mu::llvmc::ast::visitor * visitor_a) override;
				mu::vector <mu::llvmc::ast::node *> nodes;
			};
            class namespace_c : public mu::llvmc::ast::node
            {
            public:
				namespace_c (mu::string const & member_a, mu::llvmc::ast::node * node_a, mu::llvmc::template_context * context_a = nullptr);
				namespace_c (mu::llvmc::template_context * context_a = nullptr);
				namespace_c (mu::llvmc::ast::namespace_c const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
				void visit (mu::llvmc::ast::visitor * visitor_a) override;
                mu::string member;
                mu::llvmc::ast::node * node_m;
            };
            class sequence : public mu::llvmc::ast::node
            {
            public:
				sequence (mu::llvmc::ast::node * = nullptr, mu::llvmc::template_context * context_a = nullptr);
				sequence (mu::llvmc::ast::sequence const & other_a, mu::llvmc::clone_context & context_a);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context & context_a) override;
				void visit (mu::llvmc::ast::visitor * visitor_a) override;
                bool is_sequenced () const override;
                mu::llvmc::ast::node * node_m;
            };
            class visitor
            {
            public:
                void unexpected (mu::llvmc::ast::node * node_a);
                virtual void node (mu::llvmc::ast::node * node_a);
                virtual void fixed_array_type (mu::llvmc::ast::fixed_array_type * node_a);
                virtual void array_type (mu::llvmc::ast::array_type * node_a);
                virtual void constant_int (mu::llvmc::ast::constant_int * node_a);
                virtual void integer_type (mu::llvmc::ast::integer_type * node_a);
                virtual void pointer_type (mu::llvmc::ast::pointer_type * node_a);
                virtual void constant_array (mu::llvmc::ast::constant_array * node_a);
                virtual void global_variable (mu::llvmc::ast::global_variable * node_a);
                virtual void expression (mu::llvmc::ast::expression * node_a);
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
                virtual void undefined (mu::llvmc::ast::undefined * node_a);
				virtual void template_c (mu::llvmc::ast::template_c * node_a);
				virtual void template_parameter (mu::llvmc::ast::template_parameter * node_a);
                virtual void entry (mu::llvmc::ast::entry * node_a);
				virtual void set (mu::llvmc::ast::set * node_a);
                virtual void namespace_c (mu::llvmc::ast::namespace_c * node_a);
                virtual void sequence (mu::llvmc::ast::sequence * node_a);
            };
        }
    }
}