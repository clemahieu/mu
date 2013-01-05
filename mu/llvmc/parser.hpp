#pragma once

#include <mu/core/types.hpp>
#include <mu/llvmc/node_result.hpp>
#include <mu/llvmc/ast.hpp>

#include <boost/function.hpp>

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
            // Reserves a name from a lower scope, error result if name already is reserved
            virtual bool reserve (mu::string const & name_a) = 0;
            // Performs `action_a' on the value mapped to `name_a' if a mapping exists, otherwise sets error result
            virtual bool get (mu::string const & name_a, boost::function <void (mu::llvmc::ast::node *)> action_a) = 0;
            // Accept unresolved references from child and handle them if they become resolved
            virtual void accept (mu::multimap <mu::string, boost::function <void (mu::llvmc::ast::node *)>> unresolved_a) = 0;
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
            bool reserve (mu::string const & name_a) override;
            bool get (mu::string const & name_a, boost::function <void (mu::llvmc::ast::node *)> action_a) override;
            void refer (mu::string const & name_a, boost::function <void (mu::llvmc::ast::node *)> action_a);
            void accept (mu::multimap <mu::string, boost::function <void (mu::llvmc::ast::node *)>> unresolved_a) override;
            mu::map <mu::string, mu::llvmc::ast::node *> mappings;
            mu::multimap <mu::string, boost::function <void (mu::llvmc::ast::node *)>> unresolved;
            mu::llvmc::keywords * keywords;
        };
        class block : public mapping
        {
        public:
            block (mu::llvmc::mapping * parent_a);
            bool insert (mu::string const & identifier_a, mu::llvmc::ast::node * node_a);
            bool reserve (mu::string const & name_a) override;
            bool get (mu::string const & name_a, boost::function <void (mu::llvmc::ast::node *)> action_a) override;
            void refer (mu::string const & name_a, boost::function <void (mu::llvmc::ast::node *)> action_a);
            void accept (mu::multimap <mu::string, boost::function <void (mu::llvmc::ast::node *)>> unresolved_a) override;
            mu::llvmc::mapping * parent;
            mu::map <mu::string, mu::llvmc::ast::node *> mappings;
            mu::multimap <mu::string, boost::function <void (mu::llvmc::ast::node *)>> unresolved;
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
            mu::llvmc::block block;
            mu::llvmc::node_result result;
            mu::llvmc::ast::function * function_m;
            mu::llvmc::parser & parser;
        };
        class partial_ast;
        class parser
        {
        public:
            parser (mu::llvmc::partial_ast & stream_a);
            node_result parse ();
            mu::llvmc::global globals;
            mu::llvmc::mapping * current_mapping;
            mu::llvmc::module module;
            mu::llvmc::function_hook function;
            mu::llvmc::partial_ast & stream;
            mu::llvmc::keywords keywords;
        };
    }
}