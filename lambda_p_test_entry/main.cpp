#include <lambda_p_llvm_wrapper_test/tests.h>
#include <lambda_p_repl_test/tests.h>
#include <lambda_p_io_test/tests.h>
#include <lambda_p_test/tests.h>
#include <lambda_p_script_test/tests.h>
#include <lambda_p_script_io_test/tests.h>
#include <lambda_p_llvm_io_test/tests.h>

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

#include <iostream>

using namespace lambda_p_test;

int main ()
{
	llvm::InitializeNativeTarget ();
	llvm::InitializeAllAsmPrinters();
	{
		lambda_p_test::tests test;
		test.run ();
	}
	{
		lambda_p_io_test::tests test;
		test.run ();
	}
	{
		lambda_p_script_test::tests test;
		test.run ();
	}
	{
		lambda_p_script_io_test::tests test;
		test.run ();
	}
	{
		lambda_p_llvm_wrapper_test::tests test;
		test.run ();
	}
	{
		lambda_p_repl_test::tests test;
		test.run ();
	}
	{
		lambda_p_llvm_io_test::tests test;
		test.run ();
	}

	for (size_t i (0); i < 1000; ++i)
	{
		std::wcout << L'-';
	}
	return 0;
}