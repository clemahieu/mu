#pragma once

#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/io/stream_istream.hpp>
#include <mu/llvmc/parser.hpp>
#include <mu/llvmc/partial_ast.hpp>

namespace llvm
{
    class formatted_raw_ostream;
}
namespace mu
{
    namespace muc
    {
        class compiler
        {
        public:
            compiler (mu::io::stream_istream & stream, llvm::formatted_raw_ostream & output_a);
            void compile ();
            mu::io::lexer lexer;
            mu::io::stream_token stream_token;
            mu::llvmc::parser parser;
            mu::llvmc::partial_ast stream_ast;
            llvm::formatted_raw_ostream & output;
        };
    }
}