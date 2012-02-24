#include "tests.h"

#include <mu/repl_test/api_test.h>
#include <mu/repl_test/file_stream_test.h>

void mu::repl_test::tests::run ()
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