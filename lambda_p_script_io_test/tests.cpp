#include "tests.h"

#include <lambda_p_script_io_test/synthesizer.h>
#include <lambda_p_script_io_test/order.h>
#include <lambda_p_script_io_test/call.h>
#include <lambda_p_script_io_test/generator.h>
#include <lambda_p_script_io_test/builder.h>

void lambda_p_script_io_test::tests::run ()
{
	{
		call test;
		test.run ();
	}
	{
		generator test;
		test.run ();
	}
	{
		order test;
		test.run ();
	}
	{
		synthesizer test;
		test.run ();
	}
	{
		builder test;
		test.run ();
	}
}