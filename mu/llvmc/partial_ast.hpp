#pragma once

#include <mu/core/types.hpp>
#include <mu/io/stream.hpp>

namespace mu
{
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
            ~partial_ast_result ();
            mu::io::token * token;
            mu::llvmc::ast::node * ast;
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