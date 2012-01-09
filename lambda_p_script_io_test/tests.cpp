#include "tests.h"

#include <lambda_p_script_io_test/synthesizer.h>
#include <lambda_p_script_io_test/call.h>
#include <lambda_p_script_io_test/generator.h>

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
		synthesizer test;
		test.run ();
	}
}