#include <lambda_p_llvm_test/tests.h>
#include <lambda_p_repl_test/tests.h>
#include <mu/io_test/tests.h>
#include <mu/core_test/tests.h>
#include <mu/script_test/tests.h>
#include <mu/script_io_test/tests.h>

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

#include <iostream>

int main ()
{
	llvm::InitializeNativeTarget ();
	llvm::InitializeAllAsmPrinters();
	{
		mu::core_test::tests test;
		test.run ();
	}
	{
		mu::io_test::tests test;
		test.run ();
	}
	{
		mu::script_test::tests test;
		test.run ();
	}
	{
		mu::script_io_test::tests test;
		test.run ();
	}
	{
		lambda_p_llvm_test::tests test;
		test.run ();
	}
	{
		lambda_p_repl_test::tests test;
		test.run ();
	}

	for (size_t i (0); i < 1000; ++i)
	{
		std::wcout << L'-';
	}
	return 0;
}