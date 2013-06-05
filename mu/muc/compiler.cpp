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
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/InlineAsm.h>

mu::muc::compiler::compiler (mu::io::stream_istream & stream_a, llvm::formatted_raw_ostream & output_a) :
lexer (stream_a),
stream_token (lexer, 2),
parser (stream_ast),
stream_ast (stream_token, parser),
output (output_a)
{
}

void mu::muc::compiler::compile (mu::string const & name_a, mu::string const & path_a)
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
            auto entry (module.names.find (U"entry"));
            if (entry != module.names.end ())
            {
                auto entry_function (entry->second);
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
                            std::string contents;
                            llvm::raw_string_ostream stream (contents);
                            module.module->print (stream, nullptr);
                            std::cout << contents;
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

void mu::muc::compiler::inject_entry (llvm::Module * module_a, llvm::Function * entry_a)
{
    auto & context (module_a->getContext ());
    auto exit_type (llvm::FunctionType::get (llvm::Type::getVoidTy (context), llvm::ArrayRef <llvm::Type *> (), false));
    auto exit (llvm::Function::Create (exit_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage));
	auto exit_body (llvm::BasicBlock::Create (context));
	exit->getBasicBlockList ().push_back (exit_body);
	auto syscall_type (llvm::FunctionType::get (llvm::Type::getVoidTy (context), llvm::ArrayRef <llvm::Type *> (), false));
	auto exit_asm (llvm::InlineAsm::get (syscall_type, " movq $$60, %rax\n movq $$0, %rdi\n syscall", "", true));
	auto exit_call (llvm::CallInst::Create (exit_asm, llvm::ArrayRef <llvm::Value *> ()));
	exit_body->getInstList ().push_back (exit_call);
	auto unreachable (new llvm::UnreachableInst (context));
	exit_body->getInstList ().push_back (unreachable);
    module_a->getFunctionList ().push_back (exit);
    exit->addFnAttr (llvm::Attributes::NoReturn);
    auto entry_type (llvm::FunctionType::get (llvm::Type::getVoidTy (context), llvm::ArrayRef <llvm::Type *> (), false));
    auto entry (llvm::Function::Create (entry_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "\x01start"));
    auto block (llvm::BasicBlock::Create (context));
    entry->getBasicBlockList ().push_back (block);
    auto call_entry (llvm::CallInst::Create (entry_a));
    block->getInstList ().push_back (call_entry);
    auto call_exit (llvm::CallInst::Create (exit));
    block->getInstList ().push_back (call_exit);
    block->getInstList ().push_back (new llvm::UnreachableInst (context));
    module_a->getFunctionList().push_back (entry);
}