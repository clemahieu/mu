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
            class loop_result
            {
            public:
                loop_result () = default;
                loop_result (std::initializer_list <mu::llvmc::ast::node *> const &);
                loop_result (mu::llvmc::ast::loop_result const &, mu::llvmc::clone_context &);
                mu::vector <mu::llvmc::ast::node *> nodes;
            };
            class loop : public mu::llvmc::ast::node
            {
            public:
                loop (std::initializer_list <mu::llvmc::ast::node *> const &, mu::llvmc::template_context * = nullptr);
				loop (mu::llvmc::template_context * = nullptr);
				loop (mu::llvmc::ast::loop const &, mu::llvmc::clone_context &);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context &) override;
                void visit (mu::llvmc::ast::visitor *) override;
                mu::llvmc::ast::loop_result & add_branch ();
                mu::vector <mu::llvmc::ast::node *> arguments;
                mu::vector <mu::llvmc::ast::node *> parameters;
                mu::vector <mu::llvmc::ast::node *> roots;
                mu::vector <mu::llvmc::ast::loop_result> results;
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
            class function_family : public mu::llvmc::ast::node
            {
            public:
				function_family (mu::llvmc::template_context * = nullptr);
				function_family (mu::llvmc::ast::function_family const &, mu::llvmc::clone_context &);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context &) override;
                void visit (mu::llvmc::ast::visitor *) override;
            };
            class function_overload : public mu::llvmc::ast::node
            {
            public:
				function_overload (mu::llvmc::template_context * = nullptr);
				function_overload (mu::llvmc::ast::function_overload const &, mu::llvmc::clone_context &);
				mu::llvmc::ast::node * do_clone (mu::llvmc::clone_context &) override;
                void visit (mu::llvmc::ast::visitor *) override;
                mu::llvmc::ast::node * family;
                mu::llvmc::ast::node * function;
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
                void unexpected (mu::llvmc::ast::node *);
                virtual void node (mu::llvmc::ast::node *);
                virtual void fixed_array_type (mu::llvmc::ast::fixed_array_type *);
                virtual void array_type (mu::llvmc::ast::array_type *);
                virtual void constant_int (mu::llvmc::ast::constant_int *);
                virtual void integer_type (mu::llvmc::ast::integer_type *);
                virtual void pointer_type (mu::llvmc::ast::pointer_type *);
                virtual void constant_array (mu::llvmc::ast::constant_array *);
                virtual void global_variable (mu::llvmc::ast::global_variable *);
                virtual void expression (mu::llvmc::ast::expression *);
                virtual void constant_pointer_null (mu::llvmc::ast::constant_pointer_null *);
                virtual void join (mu::llvmc::ast::join *);
                virtual void loop (mu::llvmc::ast::loop *);
                virtual void unit (mu::llvmc::ast::unit *);
                virtual void asm_c (mu::llvmc::ast::asm_c *);
                virtual void value (mu::llvmc::ast::value *);
                virtual void module (mu::llvmc::ast::module *);
                virtual void number (mu::llvmc::ast::number *);
                virtual void result (mu::llvmc::ast::result *);
                virtual void element (mu::llvmc::ast::element *);
                virtual void function (mu::llvmc::ast::function *);
                virtual void unit_type (mu::llvmc::ast::unit_type *);
                virtual void loop_parameter (mu::llvmc::ast::loop_parameter *);
                virtual void parameter (mu::llvmc::ast::parameter *);
                virtual void struct_type (mu::llvmc::ast::struct_type *);
                virtual void undefined (mu::llvmc::ast::undefined *);
				virtual void template_c (mu::llvmc::ast::template_c *);
				virtual void template_parameter (mu::llvmc::ast::template_parameter *);
                virtual void entry (mu::llvmc::ast::entry *);
				virtual void set (mu::llvmc::ast::set *);
                virtual void namespace_c (mu::llvmc::ast::namespace_c *);
                virtual void sequence (mu::llvmc::ast::sequence *);
                virtual void function_family (mu::llvmc::ast::function_family *);
                virtual void function_overload (mu::llvmc::ast::function_overload *);
            };
        }
    }
}