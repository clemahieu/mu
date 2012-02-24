#include "tests.h"

#include <mu/script_io_test/synthesizer.h>
#include <mu/script_io_test/call.h>
#include <mu/script_io_test/routine.h>
#include <mu/script_io_test/builder.h>
#include <mu/script_io_test/lambda.h>

void mu::script_io_test::tests::run ()
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