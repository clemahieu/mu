#include "tests.h"

#include <lambda_p_script_io_test/synthesizer.h>
#include <lambda_p_script_io_test/call.h>
#include <lambda_p_script_io_test/routine.h>
#include <lambda_p_script_io_test/builder.h>
#include <lambda_p_script_io_test/lambda.h>

void lambda_p_script_io_test::tests::run ()
{
	{
		call test;
		test.run ();
	}
	{
		routine test;
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
	{
		lambda test;
		test.run ();
	}
}