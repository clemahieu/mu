#include <mu/muc/compiler.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/llvmc/generator.hpp>
#include <mu/core/error.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/PassManager.h>
#include <llvm/Support/raw_ostream.h>

mu::muc::compiler::compiler (mu::io::stream_istream & stream_a, llvm::formatted_raw_ostream & output_a) :
lexer (stream_a),
stream_token (lexer, 2),
parser (stream_ast),
stream_ast (stream_token, parser),
output (output_a)
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
            auto triple (llvm::sys::getDefaultTargetTriple ());
            std::string error;
            auto target (llvm::TargetRegistry::lookupTarget (triple, error));
            if (target != nullptr)
            {
                llvm::TargetOptions options;
                auto machine (target->createTargetMachine (triple, "", "", options));
                llvm::PassManager pass_manager;
                auto failed (machine->addPassesToEmitFile (pass_manager, output, llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile));
                pass_manager.run (*module);
                std::string contents;
                llvm::raw_string_ostream stream (contents);
                module->print (stream, nullptr);
                std::cout << contents;
            }
            else
            {
                std::cout << "Unable to lookup target triple: " << error;
            }
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