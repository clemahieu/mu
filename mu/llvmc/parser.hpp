#pragma once

#include <mu/core/types.hpp>
#include <mu/core/error.hpp>
#include <mu/llvmc/node_result.hpp>
#include <mu/llvmc/ast.hpp>

#include <llvm/LLVMContext.h>

#include <functional>

namespace mu
{
    namespace core
    {
        class error;
    }
    namespace io
    {
        template <typename T>
        class stream;
        class token;
        class stream_token;
    }
    namespace llvmc
    {
        class parser;
        class hook
        {
        public:
            virtual mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) = 0;
            virtual bool covering () = 0;
            virtual mu::string const & name () = 0;
        };
        class hook_result
        {
        public:
            mu::llvmc::hook * hook;
            mu::string data;
        };
        class mapping
        {
        public:
			typedef std::function <void (mu::llvmc::ast::node *, mu::core::region const &)> action_type;
			typedef std::tuple <mu::core::region, action_type> unresolved_type;
            // Reserves a name from a lower scope, error result if name already is reserved
            virtual bool reserve (mu::string const & name_a) = 0;
            // Performs `action_a' on the value mapped to `name_a' if a mapping exists, otherwise sets error result
            virtual bool get (mu::string const & name_a, mu::core::region const & region_a, action_type action_a) = 0;
            // Performs `action_a' on the value mapped to `name_a' if the mapping exists, otherwise stores `action_a' and performs when value is inserted
            virtual void refer (mu::string const & name_a, mu::core::region const & region_a, action_type action_a) = 0;
            // Maps `identifier_a' to `node_a' and calls stored actions for `identifier_a' if they exist.  Returns true if an error while inserting
            virtual bool insert (mu::string const & identifier_a, mu::llvmc::ast::node * node_a) = 0;
            // Accept unresolved references from child and handle them if they become resolved
            virtual void accept (mu::multimap <mu::string, unresolved_type> unresolved_a) = 0;
        };
        class keywords
        {
        public:
            bool insert (mu::string const & identifier_a, mu::llvmc::hook * hook_a);
            // Returns the hook covering `identifier_a' if one exists
            hook_result get_hook (mu::string const & identifier_a);
            mu::map <mu::string, mu::llvmc::hook *> mappings;
        };
        class global : public mapping
        {
        public:
            global (mu::llvmc::keywords * keywords_a);
            bool insert (mu::string const & identifier_a, mu::llvmc::ast::node * node_a) override;
            bool reserve (mu::string const & name_a) override;
            bool get (mu::string const & name_a, mu::core::region const & region_a, action_type action_a) override;
            void refer (mu::string const & name_a, mu::core::region const & region_a, action_type action_a) override;
            void accept (mu::multimap <mu::string, unresolved_type> unresolved_a) override;
            mu::map <mu::string, mu::llvmc::ast::node *> mappings;
            mu::multimap <mu::string, unresolved_type> unresolved;
            mu::llvmc::keywords * keywords;
        };
        class block : public mapping
        {
        public:
            block (mu::llvmc::mapping * parent_a);
            ~block ();
            bool insert (mu::string const & identifier_a, mu::llvmc::ast::node * node_a) override;
            bool reserve (mu::string const & name_a) override;
            bool get (mu::string const & name_a, mu::core::region const & region_a, action_type action_a) override;
            void refer (mu::string const & name_a, mu::core::region const & region_a, action_type action_a) override;
            void accept (mu::multimap <mu::string, unresolved_type> unresolved_a) override;
            mu::llvmc::mapping * parent;
            mu::map <mu::string, mu::llvmc::ast::node *> mappings;
            mu::multimap <mu::string, unresolved_type> unresolved;
        };
        template <typename T>
        class scope_set
        {
        public:
            scope_set (T & pointer_a, T value_a)
            : pointer (pointer_a)
            {
                pointer_a = value_a;
            }
            ~scope_set ()
            {
                pointer = nullptr;
            }
            T & pointer;
        };
        class module : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class function_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class set_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class let_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class function
        {
        public:
            function (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a);
            ~function ();
            void parse ();
            void parse_parameters ();
            void parse_parameter (bool & done_a);
            void parse_body ();
            void parse_results ();
            void parse_result_set ();
            mu::llvmc::block block;
            mu::llvmc::node_result result;
            mu::llvmc::ast::function * function_m;
            mu::llvmc::parser & parser;
			mu::core::region first;
        };
        class expression
        {
        public:
            expression (mu::core::region const & region_a, mu::llvmc::parser & parser_a);
            void parse ();
            mu::llvmc::node_result result;
            mu::llvmc::parser & parser;
            mu::core::region region;
        };
        class int_type : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class ptr_type : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class number : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class constant_int : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class loop_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class loop
        {
        public:
            loop (mu::llvmc::parser & parser_a);
            void parse ();
            void parse_arguments ();
            void parse_binds ();
            void parse_body ();
            void parse_results ();
            mu::llvmc::ast::loop * loop_m;
            mu::llvmc::node_result result;
            mu::llvmc::parser & parser;
        };
        class asm_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class array_type : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class constant_array : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class partial_ast_result
        {
        public:
            partial_ast_result (mu::io::token * token_a, mu::llvmc::ast::node * ast_a, mu::core::error * error_a);
            partial_ast_result (mu::llvmc::partial_ast_result const & other_a);
            mu::llvmc::partial_ast_result & operator = (mu::llvmc::partial_ast_result const & other_a);
            bool valid ();
            mu::io::token * token;
            mu::llvmc::ast::node * ast;
            mu::core::error * error;
        };
		class string_hook : public mu::llvmc::hook
		{
		public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
		};
		class ascii_hook : public mu::llvmc::hook
		{
		public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
		};
        class global_variable : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class constant_pointer_null : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class join_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class undefined_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class struct_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
        };
        class parser_frame
        {
        public:
            mu::core::position position;
            mu::string const * name;
        };
		class template_hook : public mu::llvmc::hook
		{
		public:
            mu::llvmc::node_result parse (mu::core::region const & region_a, mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::string const & name () override;
		};
        class parser
        {
        public:
            parser (mu::io::stream_token & stream_a);
            node_result parse ();
            void consume ();
            template <typename T>
            mu::core::error * parse_ast_or_refer (T op);
			template <typename T, typename U>
			mu::core::error * parse_ast_or_refer_or_right_square (T op, U right_square_op, char32_t const * error_message_a, mu::core::error_type error_type_a);
            template <typename T>
            mu::core::error * parse_identifier (T identifier_op, char32_t const * error_message_a, mu::core::error_type error_type_a);
            template <typename T, typename U>
            mu::core::error * parse_identifier_or_right_square (T identifier_op, U right_square_op, char32_t const * error_message_a, mu::core::error_type error_type_a);
            template <typename T, typename U>
            mu::core::error * parse_left_or_right_square (T left_square_op, U right_square_op, char32_t const * error_message_a, mu::core::error_type error_type_a);
            template <typename T, typename U, typename V>
            mu::core::error * parse_ast_or_refer_or_right_square_or_terminator (T node_op, U right_square_op, V terminator_op, char32_t const * error_message_a, mu::core::error_type error_type_a);
            mu::core::error * parse_left_square_required (char32_t const * error_message_a, mu::core::error_type error_type_a);
            mu::llvmc::partial_ast_result peek ();
            mu::llvmc::global builtins;
            mu::llvmc::block globals;
            mu::llvmc::mapping * current_mapping;
            mu::llvmc::module module;
            mu::llvmc::function_hook function;
            mu::llvmc::asm_hook asm_hook;
            mu::llvmc::int_type int_type;
            mu::llvmc::set_hook set_hook;
            mu::llvmc::let_hook let_hook;
            mu::llvmc::loop_hook loop_hook;
            mu::llvmc::ptr_type ptr_type;
            mu::llvmc::array_type array_type;
			mu::llvmc::string_hook string_hook;
			mu::llvmc::ascii_hook ascii_hook;
            mu::llvmc::join_hook join_hook;
            mu::llvmc::undefined_hook undefined_hook;
            mu::llvmc::struct_hook struct_hook;
            mu::llvmc::constant_array constant_array;
            mu::llvmc::number number;
            mu::llvmc::constant_int constant_int;
            mu::llvmc::global_variable global_variable;
            mu::llvmc::constant_pointer_null constant_pointer_null;
            mu::io::stream_token & stream;
            mu::llvmc::keywords keywords;
			mu::llvmc::template_hook template_hook;
            std::vector <mu::llvmc::parser_frame> parse_stack;
        };
        class parser_error : public mu::core::error
        {
        public:
            parser_error (char32_t const * message_a, mu::core::error_type type_a, mu::core::region const & region_a, mu::llvmc::parser & parser_a);
            void output (std::ostream & out) override;
            mu::core::error_type type () override;
            mu::core::region region () override;
            mu::core::error_type type_m;
            mu::string message;
			mu::core::region region_m;
            std::vector <mu::llvmc::parser_frame> parse_stack;
        };
        class parser_context
        {
        public:
            parser_context (mu::llvmc::parser & parser_a, mu::string const * name_a);
            ~parser_context ();
            mu::llvmc::parser & parser;
        };
    }
}