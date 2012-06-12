#include <mu/llvm_test/tests.h>
#include <mu/repl_test/tests.h>
#include <mu/script_test/tests.h>

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

#include <gtest/gtest.h>

#include <iostream>

int main (int argc, char** argv)
{
	llvm::InitializeNativeTarget ();
	llvm::InitializeNativeTargetAsmPrinter();
    testing::InitGoogleTest(&argc, argv);
    auto result (RUN_ALL_TESTS());
	{
		mu::script_test::tests test;
		test.run ();
	}
	{
		mu::repl_test::tests test;
		test.run ();
	}
	{
		mu::llvm_test::tests test;
		test.run ();
	}
	return result;
}