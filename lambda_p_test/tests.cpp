#include "tests.h"

#include <lambda_p_test/simple_compile_test_1.h>
#include <lambda_p_test/routine_builder_test.h>
#include <lambda_p_test/wistream_input_test.h>
#include <lambda_p_test/filesystem_test.h>
#include <lambda_p_test/istream_input_test.h>
#include <lambda_p_test/directory_iterator_test.h>
#include <lambda_p_test/list_iterator.h>

void lambda_p_test::tests::run ()
{
	{
		list_iterator test;
		test.run ();
	}
	{
		simple_compile_test_1 test;
		test.run ();
	}
	{
		wistream_input_test test;
		test.run ();
	}
	{
		routine_builder_test test;
		test.run ();
	}
	{
		filesystem_test test;
		test.run ();
	}
	{
		istream_input_test test;
		test.run ();
	}
	{
		directory_iterator_test test;
		test.run ();
	}
}