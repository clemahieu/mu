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
        class partial_ast
        {
        public:
            partial_ast (mu::io::stream_token & tokens_a, mu::llvmc::parser & parser_a);
            mu::io::stream_token & tokens;
            mu::llvmc::parser & parser;
        };
    }
}