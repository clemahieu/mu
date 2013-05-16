#include <mu/muc/compiler.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/llvmc/generator.hpp>
#include <mu/core/error.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Module.h>

mu::muc::compiler::compiler (mu::io::stream_istream & stream_a) :
lexer (stream_a),
stream_token (lexer, 2),
parser (stream_ast),
stream_ast (stream_token, parser)
{
}

void mu::muc::compiler::compile ()
{
    auto parse_result (parser.parse ());
    if (parse_result.error == nullptr)
    {
        mu::llvmc::analyzer analyzer;
        auto analyze_result (analyzer.analyze (parse_result.node));
        if (analyze_result.error == nullptr)
        {
            mu::llvmc::generator generator;
            llvm::LLVMContext context;
            auto module (generator.generate (context, analyze_result.module));
            std::string contents;
            llvm::raw_string_ostream stream (contents);
            module->print (stream, nullptr);
            std::cout << contents;
        }
        else
        {
            std::cout << "Error analyzing (" << (uint64_t)analyze_result.error->type () << "): " << analyze_result.error->string () << '\n';
        }
    }
    else
    {
        std::cout << "Error parsing (" << (uint64_t)parse_result.error->type () << "): " << parse_result.error->string () << '\n';
    }
}