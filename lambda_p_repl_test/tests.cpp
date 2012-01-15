#include "tests.h"

#include <lambda_p_repl_test/api_test.h>
#include <lambda_p_repl_test/file_stream_test.h>

void lambda_p_repl_test::tests::run ()
{
	{
		api_test test;
		test.run ();
	}
	{
		file_stream_test test;
		test.run ();
	}
}