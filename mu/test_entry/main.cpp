#include <mu/core_test/tests.h>
#include <mu/io_test/tests.h>
#include <mu/llvm_test/tests.h>
#include <mu/repl_test/tests.h>
#include <mu/script_test/tests.h>

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

#include <iostream>

int main ()
{
	llvm::InitializeNativeTarget ();
	llvm::InitializeNativeTargetAsmPrinter();
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
	//{
	//	mu::llvm_test::tests test;
	//	test.run ();
	//}
	//{
	//	mu::repl_test::tests test;
	//	test.run ();
	//}

	for (size_t i (0); i < 1000; ++i)
	{
		std::wcout << L'-';
	}
	return 0;
}