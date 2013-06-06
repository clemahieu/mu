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
            virtual mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) = 0;
            virtual bool covering () = 0;
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
			typedef std::function <void (mu::llvmc::ast::node *)> action_type;
            // Reserves a name from a lower scope, error result if name already is reserved
            virtual bool reserve (mu::string const & name_a) = 0;
            // Performs `action_a' on the value mapped to `name_a' if a mapping exists, otherwise sets error result
            virtual bool get (mu::string const & name_a, mu::core::region const & region_a, action_type action_a) = 0;
            // Performs `action_a' on the value mapped to `name_a' if the mapping exists, otherwise stores `action_a' and performs when value is inserted
            virtual void refer (mu::string const & name_a, mu::core::region const & region_a, action_type action_a) = 0;
            // Maps `identifier_a' to `node_a' and calls stored actions for `identifier_a' if they exist.  Returns true if an error while inserting
            virtual bool insert (mu::string const & identifier_a, mu::llvmc::ast::node * node_a) = 0;
            // Accept unresolved references from child and handle them if they become resolved
            virtual void accept (mu::multimap <mu::string, action_type> unresolved_a) = 0;
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
            void accept (mu::multimap <mu::string, action_type> unresolved_a) override;
            mu::map <mu::string, mu::llvmc::ast::node *> mappings;
            mu::multimap <mu::string, action_type> unresolved;
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
            void accept (mu::multimap <mu::string, action_type> unresolved_a) override;
            mu::llvmc::mapping * parent;
            mu::map <mu::string, mu::llvmc::ast::node *> mappings;
            mu::multimap <mu::string, action_type> unresolved;
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
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
            mu::llvmc::availability::module * current_module;
        };
        class function_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
        };
        class set_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
        };
        class let_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
        };
        class function
        {
        public:
            function (mu::string const & data_a, mu::llvmc::parser & parser_a);
            ~function ();
            void parse ();
            void parse_name ();
            void parse_parameters ();
            void parse_parameter (bool & done_a);
            void parse_body ();
            void parse_results ();
            void parse_result_set ();
            mu::llvmc::block block;
            mu::llvmc::node_result result;
            mu::llvmc::ast::function * function_m;
            mu::llvmc::parser & parser;
        };
        class expression
        {
        public:
            expression (mu::llvmc::parser & parser_a);
            void parse ();
            mu::llvmc::node_result result;
            mu::llvmc::parser & parser;
        };
        class int_type : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
        };
        class ptr_type : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
        };
        class number : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
        };
        class constant_int : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
        };
        class loop_hook : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
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
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            bool covering () override;
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
            mu::llvmc::partial_ast_result peek ();
            mu::llvmc::global globals;
            mu::llvmc::mapping * current_mapping;
            mu::llvmc::module module;
            mu::llvmc::function_hook function;
            mu::llvmc::asm_hook asm_hook;
            mu::llvmc::int_type int_type;
            mu::llvmc::set_hook set_hook;
            mu::llvmc::let_hook let_hook;
            mu::llvmc::loop_hook loop_hook;
            mu::llvmc::ptr_type ptr_type;
            mu::llvmc::number number;
            mu::llvmc::constant_int constant_int;
            mu::io::stream_token & stream;
            mu::llvmc::keywords keywords;
        };
    }
}