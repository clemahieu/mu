#include "tests.h"

#include <lambda_p_script_test/routine.h>
#include <lambda_p_script_test/call.h>
#include <lambda_p_script_test/constant.h>
#include <lambda_p_script_test/expression.h>
#include <lambda_p_script_test/reference.h>

void lambda_p_script_test::tests::run ()
{
	{
		reference test;
		test.run ();
	}
	{
		expression test;
		test.run ();
	}
	{
		constant test;
		test.run ();
	}
	{
		call test;
		test.run ();
	}
	{
		routine test;
		test.run ();
	}
}