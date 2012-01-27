#include "tests.h"

#include <lambda_p_llvm_test/module/get_package.h>
#include <lambda_p_llvm_test/module/add_package.h>
#include <lambda_p_llvm_test/linker/link_modules.h>
#include <lambda_p_llvm_test/analyzer.h>
#include <lambda_p_llvm_test/extension.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>

void lambda_p_llvm_test::tests::run ()
{
	{
		llvm::LLVMContext context;
		llvm::Module (llvm::StringRef (), context);
		assert ("No module name");
	}
	{
		llvm::LLVMContext context;
		auto function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage));
		auto type (function->getType ());
		auto function_type (function->getFunctionType ());
		assert (type->isPointerTy ());
		assert (type->getContainedType (0)->isFunctionTy ());
		assert (function_type->getReturnType () == llvm::Type::getVoidTy (context));
		assert (function_type->param_begin () == function_type->param_end ());
	}
	{
		llvm::LLVMContext context;
	}
	{
		lambda_p_llvm_test::module::get_package test;
		test.run ();
	}
	{
		lambda_p_llvm_test::module::add_package test;
		test.run ();
	}
	{
		lambda_p_llvm_test::linker::link_modules test;
		test.run ();
	}
	{
		analyzer test;
		test.run ();
	}
	{
		extension test;
		test.run ();
	}
}