#include <lambda_p_test/simple_test_1.h>
#include <lambda_p_test/simple_lexer_test_1.h>
#include <lambda_p_test/simple_parser_test_1.h>
#include <lambda_p_test/simple_compile_test_1.h>
#include <lambda_p_test/routine_binder_test_1.h>
#include <lambda_p_test/package_test_1.h>
#include <lambda_p_test/abort_binder_test_1.h>
#include <lambda_p_test/jit_test_1.h>
#include <lambda_p_test/data_to_string_binder_test_1.h>
#include <lambda_p_test/echo_binder_test.h>
#include <lambda_p_test/constant_int_binder_test_1.h>
#include <lambda_p_test/routine_input_test_1.h>

using namespace lambda_p_test;

int main ()
{
	{
		simple_test_1 test;
		test.run ();
	}
	{
		simple_lexer_test_1 test;
		test.run ();
	}
	{
		simple_parser_test_1 test;
		test.run ();
	}
	{
		simple_compile_test_1 test;
		test.run ();
	}
	{
		routine_binder_test_1 test;
		test.run ();
	}
	{
		package_test_1 test;
		test.run ();
	}
    {
        abort_binder_test_1 test;
        test.run ();
    }
    {
        jit_test_1 test;
        test.run ();
    }
    {
        data_to_string_binder_test_1 test;
        test.run ();
    }
    {
        echo_binder_test test;
        test.run ();
    }
	{
		constant_int_binder_test_1 test;
		test.run ();
	}
	{
		routine_input_test_1 test;
		test.run ();
	}
	return 0;
}