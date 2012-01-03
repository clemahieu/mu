#include "tests.h"

#include <lambda_p_test/abort_binder_test_1.h>
#include <lambda_p_test/constant_int_binder_test_1.h>
#include <lambda_p_test/execution_engine_test.h>
#include <lambda_p_test/generator_test.h>
#include <lambda_p_test/jit_test_1.h>
#include <lambda_p_test/link_test.h>
#include <lambda_p_test/overlay_binder_test.h>
#include <lambda_p_test/type_inference_test.h>

void lambda_p_llvm_test::tests::run ()
{
    {
        abort_binder_test_1 test;
        test.run ();
    }
	{
		constant_int_binder_test_1 test;
		test.run ();
	}
	{
		execution_engine_test test;
		test.run ();
	}
	{
		generator_test test;
		test.run ();
	}
    {
        jit_test_1 test;
        test.run ();
    }
	{
		link_test test;
		test.run ();
	}
	{
		overlay_binder_test test;
		test.run ();
	}
	{
		type_inference_test test;
		test.run ();
	}
}