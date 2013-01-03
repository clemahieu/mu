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
        class hook : public mu::llvmc::ast::node
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
            // Returns the hook covering `identifier_a' if one exists
            hook_result get_hook (mu::string const & identifier_a);
            // Perform `action_a' on the node mapped to `identifier_a', if it's not mapped, store `action_a' and perform when resolved
            void refer (mu::string const & identifier_a, boost::function <void (mu::llvmc::ast::node *)> action_a);
            // Create mapping of `identifier_a' to `node_a', if actions for this identifier have been stored, perform them.
            // Return if mapping already existed.
            bool map (mu::string const & identifier_a, mu::llvmc::ast::node * node_a);
        private:
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
        class function : public mu::llvmc::hook
        {
        public:
            mu::llvmc::node_result parse (mu::string const & data_a, mu::llvmc::parser & parser_a) override;
            void parse_name (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a);
            void parse_parameters (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a);
            void parse_parameter (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a, bool & done_a);
            void parse_body (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a);
            void parse_results (mu::llvmc::node_result & result_a, mu::llvmc::ast::function * function_a, mu::llvmc::parser & parser_a);
            bool covering () override;
        };
        class parser
        {
        public:
            parser (mu::io::stream <mu::io::token *> & stream_a);
            node_result parse ();
            mu::llvmc::module module;
            mu::llvmc::function function;
            mu::io::stream <mu::io::token *> & stream;
            mu::llvmc::mapping mapping;
        };
    }
}