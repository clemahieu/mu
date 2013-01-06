#pragma once

#include <mu/core/types.hpp>
#include <mu/io/stream.hpp>

namespace mu
{
    namespace core
    {
        class error;
    }
    namespace io
    {
        class stream_token;
        class token;
    }
    namespace llvmc
    {
        class parser;
        namespace ast
        {
            class node;
        }
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
        class partial_ast
        {
        public:
            partial_ast (mu::io::stream_token & tokens_a, mu::llvmc::parser & parser_a);
            void consume ();
            mu::llvmc::partial_ast_result & peek ();
        private:
            void refill ();
            mu::llvmc::partial_ast_result item;
            mu::io::stream_token & tokens;
            mu::llvmc::parser & parser;
        };
    }
}