#include <mu/llvmc/compiler.hpp>

#include <mu/llvmc/analyzer.hpp>
#include <mu/llvmc/generator.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/PassManager.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/InlineAsm.h>
#include <llvm/Analysis/Verifier.h>

mu::llvmc::compiler::compiler (mu::io::stream_istream & stream_a, llvm::formatted_raw_ostream & output_a) :
lexer (stream_a),
stream_token (lexer, 2),
parser (stream_token),
output (output_a)
{
}

void mu::llvmc::compiler::compile (mu::string const & name_a, mu::string const & path_a)
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
            auto module (generator.generate (context, analyze_result.module, name_a, path_a, 0));
            std::string contents;
            llvm::raw_string_ostream stream (contents);
            module.module->print (stream, nullptr);
            std::cout << contents;
            std::string info;
            assert (!llvm::verifyModule (*module.module, llvm::VerifierFailureAction::ReturnStatusAction, &info));
            if (module.entry != nullptr)
            {
                auto entry_function (module.entry);
                if (entry_function->getReturnType ()->isVoidTy ())
                {
                    if (entry_function->getArgumentList ().empty ())
                    {
                        inject_entry (module.module, entry_function);
                        auto triple (llvm::sys::getDefaultTargetTriple ());
                        std::string error;
                        auto target (llvm::TargetRegistry::lookupTarget (triple, error));
                        if (target != nullptr)
                        {
                            module.module->setTargetTriple (llvm::sys::getDefaultTargetTriple ());
                            llvm::TargetOptions options;
                            auto machine (target->createTargetMachine (triple, "", "", options, llvm::Reloc::Default, llvm::CodeModel::Default, llvm::CodeGenOpt::None));
                            llvm::PassManager pass_manager;
                            auto failed (machine->addPassesToEmitFile (pass_manager, output, llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile));
                            pass_manager.run (*module.module);
                        }
                        else
                        {
                            std::cout << "Unable to lookup target triple: " << error;
                        }
                    }
                    else
                    {
                        std::cout << "Entry point must not take any arguments";
                    }
                }
                else
                {
                    std::cout << "Entry point must return void";
                }
            }
            else
            {
                std::cout << "Module has no function named \"entry\" to use as entry point";
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

void mu::llvmc::compiler::inject_entry (llvm::Module * module_a, llvm::Function * entry_a)
{
    auto & context (module_a->getContext ());
    auto entry_type (llvm::FunctionType::get (llvm::Type::getVoidTy (context), llvm::ArrayRef <llvm::Type *> (), false));
    auto entry (llvm::Function::Create (entry_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "\x01start"));
    auto block (llvm::BasicBlock::Create (context));
    entry->getBasicBlockList ().push_back (block);
    auto call_entry (llvm::CallInst::Create (entry_a));
    block->getInstList ().push_back (call_entry);
    block->getInstList ().push_back (new llvm::UnreachableInst (context));
    module_a->getFunctionList().push_back (entry);
}