#include "tests.h"

#include <lambda_p_llvm_io_test/synthesizer.h>

void lambda_p_llvm_io_test::tests::run ()
{
	{
		synthesizer test;
		test.run ();
	}
}
