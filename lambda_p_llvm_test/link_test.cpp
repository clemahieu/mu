#include "link_test.h"

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Linker.h>

void lambda_p_test::link_test::run ()
{
	run_1 ();
}

void lambda_p_test::link_test::run_1 ()
{	
	llvm::LLVMContext context;
	llvm::Module * m1 (new llvm::Module (llvm::StringRef ("m1"), context));
	llvm::Module * m2 (new llvm::Module (llvm::StringRef ("m2"), context));
	llvm::Function * m1f1 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt8PtrTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine ("f1")));
	m1->getFunctionList ().push_back (m1f1);
	m1f1->getBasicBlockList ().push_back (llvm::BasicBlock::Create (context));
	llvm::Function * m2f1 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt8PtrTy (context), false), llvm::GlobalValue::ExternalLinkage, llvm::Twine ("f1")));
	m2->getFunctionList ().push_back (m2f1);
	m2f1->getBasicBlockList ().push_back (llvm::BasicBlock::Create (context));
	std::string error;
	llvm::Linker::LinkModules (m1, m2, &error);
	assert (!error.empty ());
}