#include "tests.h"

#include <lambda_p_test/filesystem_test.h>
#include <lambda_p_test/directory_iterator_test.h>
#include <lambda_p_test/visitor.h>
#include <lambda_p_test/list.h>

void lambda_p_test::tests::run ()
{
	{
		list test;
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
	{
		visitor test;
		test.run ();
	}
}