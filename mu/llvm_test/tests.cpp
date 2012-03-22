#include <mu/llvm_test/tests.h>

#include <mu/llvm_test/module/get_package.h>
#include <mu/llvm_test/module/add_package.h>
#include <mu/llvm_test/linker/link_modules.h>
#include <mu/llvm_test/extension.h>
#include <mu/llvm_test/types/integer.h>
#include <mu/llvm_test/basic_block/insert.h>
#include <mu/llvm_test/instruction_package.h>
#include <mu/llvm_test/function_type/create.h>
#include <mu/llvm_test/analyzer/operation.h>
#include <mu/llvm_test/function/create.h>
#include <mu/llvm_test/constant_string/extension.h>
#include <mu/llvm_test/instructions/call.h>
#include <mu/llvm_test/constant_string/create.h>
#include <mu/llvm_test/global_variable/create_set.h>
#include <mu/llvm_test/ccall/operation.h>
#include <mu/llvm_test/instructions/trunc.h>
#include <mu/llvm_test/basic_block/instruction_insert.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Constants.h>

void mu::llvm_test::tests::run ()
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
		mu::llvm_test::module::get_package test;
		test.run ();
	}
	{
		mu::llvm_test::module::add_package test;
		test.run ();
	}
	{
		mu::llvm_test::linker::link_modules test;
		test.run ();
	}
	{
		mu::llvm_test::constant_string::extension test;
		test.run ();
	}
	{
		extension test;
		test.run ();
	}
	{
		mu::llvm_test::types::integer test;
		test.run ();
	}
	{
		mu::llvm_test::basic_block::insert test;
		test.run ();
	}
	{
		mu::llvm_test::basic_block::instruction_insert test;
		test.run ();
	}
	{
		mu::llvm_test::instruction_package test;
		test.run ();
	}
	{
		mu::llvm_test::function_type::create test;
		test.run ();
	}
	{
		mu::llvm_test::constant_string::create test;
		test.run ();
	}
	{
		mu::llvm_test::global_variable::create_set test;
		test.run ();
	}
	{
		mu::llvm_test::instructions::trunc test;
		test.run ();
	}
	{
		mu::llvm_test::analyzer::operation test;
		test.run ();
	}
	{
		mu::llvm_test::function::create test;
		test.run ();
	}
	{
		mu::llvm_test::instructions::call test;
		test.run ();
	}
	{
		mu::llvm_test::ccall::operation test;
		test.run ();
	}
}