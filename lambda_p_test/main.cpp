#include <lambda_p_test/simple_test_1.h>
#include <lambda_p_test/simple_lexer_test_1.h>
#include <lambda_p_test/simple_parser_test_1.h>
#include <lambda_p_test/simple_compile_test_1.h>
#include <lambda_p_test/bind_procedure_test_1.h>
#include <lambda_p_test/package_test_1.h>
#include <lambda_p_test/abort_binder_test_1.h>
#include <lambda_p_test/jit_test_1.h>
#include <lambda_p_test/data_to_string_binder_test_1.h>
#include <lambda_p_test/echo_binder_test.h>
#include <lambda_p_test/constant_int_binder_test_1.h>
#include <lambda_p_test/routine_input_test_1.h>
#include <lambda_p_test/node_instances_test_1.h>
#include <lambda_p_test/routine_binder_test.h>
#include <lambda_p_test/noop_closure_test.h>
#include <lambda_p_test/unbindable_statement_test.h>
#include <lambda_p_test/generator_test.h>
#include <lambda_p_test/routine_builder_test.h>
#include <lambda_p_test/function_binder_test.h>
#include <lambda_p_test/list_test.h>
#include <lambda_p_test/wistream_input_test.h>

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
		bind_procedure_test_1 test;
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
		wistream_input_test test;
		test.run ();
	}
	{
		routine_input_test_1 test;
		test.run ();
	}
	{
		node_instances_test_1 test;
		test.run ();
	}
	{
		routine_binder_test test;
		test.run ();
	}
	{
		unbindable_statement_test test;
		test.run ();
	}
	{
		noop_closure_test test;
		test.run ();
	}
	{
		function_binder_test test;
		test.run ();
	}
	{
		routine_builder_test test;
		test.run ();
	}
	{
		list_test test;
		test.run ();
	}
	{
		generator_test test;
		test.run ();
	}
	return 0;
}