#pragma once

#include <mu/io/lexer.hpp>
#include <mu/io/stream_token.hpp>
#include <mu/io/stream_istream.hpp>
#include <mu/llvmc/parser.hpp>

namespace llvm
{
    class formatted_raw_ostream;
    class Function;
	class raw_pwrite_stream;
}
namespace mu
{
    namespace llvmc
    {
        class compiler
        {
        public:
            compiler (mu::io::string_range const &, llvm::raw_pwrite_stream & output_a);
            void compile (mu::string const & name_a, mu::string const & path_a);
            void inject_entry (llvm::Module & module_a, llvm::Function * entry);
            mu::io::lexer lexer;
            mu::io::stream_token stream_token;
            mu::llvmc::parser parser;
            llvm::raw_pwrite_stream & output;
        };
    }
}