#pragma once

#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/io/stream_istream.hpp>
#include <mu/llvmc/parser.hpp>
#include <mu/llvmc/partial_ast.hpp>

namespace llvm
{
    class formatted_raw_ostream;
    class Function;
}
namespace mu
{
    namespace llvmc
    {
        class compiler
        {
        public:
            compiler (mu::io::stream_istream & stream, llvm::formatted_raw_ostream & output_a);
            void compile (mu::string const & name_a, mu::string const & path_a);
            void inject_entry (llvm::Module * module_a, llvm::Function * entry);
            mu::io::lexer lexer;
            mu::io::stream_token stream_token;
            mu::llvmc::parser parser;
            llvm::formatted_raw_ostream & output;
        };
    }
}