#include "tests.h"

#include <lambda_p_llvm_test/module/get_package.h>
#include <lambda_p_llvm_test/module/add_package.h>
#include <lambda_p_llvm_test/linker/link_modules.h>
#include <lambda_p_llvm_test/analyzer.h>
#include <lambda_p_llvm_test/extension.h>
#include <lambda_p_llvm_test/types/integer.h>
#include <lambda_p_llvm_test/basic_block/insert.h>
#include <lambda_p_llvm_test/instruction_package.h>
#include <lambda_p_llvm_test/function_type/create.h>
#include <lambda_p_llvm_test/synthesizer/operation.h>
#include <lambda_p_llvm_test/function/create.h>
#include <lambda_p_llvm_test/constant_string/extension.h>

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
		llvm::LLVMContext & c2 (context);
		llvm::LLVMContext * c3 (&c2);
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
		lambda_p_llvm_test::constant_string::extension test;
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
	{
		lambda_p_llvm_test::types::integer test;
		test.run ();
	}
	{
		lambda_p_llvm_test::basic_block::insert test;
		test.run ();
	}
	{
		lambda_p_llvm_test::instruction_package test;
		test.run ();
	}
	{
		lambda_p_llvm_test::function_type::create test;
		test.run ();
	}
	{
		lambda_p_llvm_test::synthesizer::operation test;
		test.run ();
	}
	{
		lambda_p_llvm_test::function::create test;
		test.run ();
	}
}