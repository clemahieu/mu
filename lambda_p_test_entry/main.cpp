//#include <lambda_p_kernel_test/tests.h>
//#include <lambda_p_llvm_test/tests.h>
//#include <lambda_p_repl_test/tests.h>
//#include <lambda_p_serialization_test/tests.h>
#include <lambda_p_test/tests.h>

#include <llvm/Target/TargetSelect.h>

#include <iostream>

using namespace lambda_p_test;

int main ()
{
    llvm::InitializeNativeTarget ();
	{
		lambda_p_test::tests test;
		test.run ();
	}
	//{
	//	lambda_p_serialization_test test;
	//	test.run ();
	//}
	//{
	//	lambda_p_kernel_test::tests test;
	//	test.run ();
	//}
	//{
	//	lambda_p_llvm_test::tests test;
	//	test.run ();
	//}
	//{
	//	lambda_p_repl_test::tests test;
	//	test.run ();
	//}

	for (size_t i (0); i < 1000; ++i)
	{
		std::wcout << L'-';
	}
	return 0;
}