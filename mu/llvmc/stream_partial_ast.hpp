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
        class partial_ast
        {
        public:
            ~partial_ast ();
            mu::io::token * token;
            mu::llvmc::ast::node * ast;
        };
        class stream_partial_ast : mu::io::stream <mu::llvmc::partial_ast>
        {
        public:
            stream_partial_ast (mu::io::stream_token & tokens_a, mu::llvmc::parser & parser_a, size_t size_a);
            void consume (size_t size_a) override;
            mu::llvmc::partial_ast & operator [] (size_t size_a) override;
            size_t size () override;
        private:
            void refill ();
            mu::circular_buffer <mu::llvmc::partial_ast> buffer;
            mu::io::stream_token & tokens;
            mu::llvmc::parser & parser;
        };
    }
}