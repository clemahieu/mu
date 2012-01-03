#include "tests.h"

#include <lambda_p_test/scatter.h>
#include <lambda_p_test/filesystem_test.h>
#include <lambda_p_test/directory_iterator_test.h>
#include <lambda_p_test/routine.h>
#include <lambda_p_test/identity.h>

void lambda_p_test::tests::run ()
{
	{
		identity test;
		test.run ();
	}
	{
		scatter test;
		test.run ();
	}
	{
		routine test;
		test.run ();
	}
	{
		filesystem_test test;
		test.run ();
	}
	{
		directory_iterator_test test;
		test.run ();
	}
}