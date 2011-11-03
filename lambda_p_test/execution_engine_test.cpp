#include "execution_engine_test.h"

#include <llvm/LLVMContext.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Linker.h>

void lambda_p_test::execution_engine_test::run ()
{
	run_1 ();
}

void lambda_p_test::execution_engine_test::run_1 ()
{
	llvm::LLVMContext context;
	llvm::Type const * size_t_type (llvm::IntegerType::get (context, sizeof (size_t) * 8));
	llvm::Module * m1 (new llvm::Module (llvm::StringRef ("m1"), context));
	llvm::Module * m2 (new llvm::Module (llvm::StringRef ("m2"), context));
	llvm::Function * start (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage));
	m1->getFunctionList ().push_back (start);
	std::vector <llvm::Type const *> arguments;
	arguments.push_back (size_t_type);
	llvm::Function * malloc_dec (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt8PtrTy (context), arguments, false), llvm::GlobalValue::ExternalLinkage, llvm::Twine ("mal")));
	m1->getFunctionList ().push_back (malloc_dec);
	llvm::Function * malloc_def (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt8PtrTy (context), arguments, false), llvm::GlobalValue::ExternalLinkage, llvm::Twine ("mal")));
	m2->getFunctionList ().push_back (malloc_def);
	llvm::BasicBlock * block (llvm::BasicBlock::Create (context));
	start->getBasicBlockList ().push_back (block);
	llvm::CallInst * call (llvm::CallInst::Create (malloc_dec, llvm::ConstantInt::get (size_t_type, 0)));
	block->getInstList ().push_back (call);
	llvm::ReturnInst * ret (llvm::ReturnInst::Create (context));
	block->getInstList ().push_back (ret);
	llvm::EngineBuilder builder (m1);
	builder.setEngineKind (llvm::EngineKind::JIT);
	std::string error;
	builder.setErrorStr (&error);
	llvm::ExecutionEngine * engine (builder.create ());
	llvm::Linker::LinkModules (m1, m2, &error);
	engine->addGlobalMapping (malloc_dec, (void *)::malloc);
	engine->runFunction (start, std::vector <llvm::GenericValue> ());
	assert (true);
}