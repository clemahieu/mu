#include "tests.h"

#include <mu/core_test/filesystem_test.h>
#include <mu/core_test/directory_iterator_test.h>
#include <mu/core_test/visitor.h>
#include <mu/core_test/list.h>
#include <mu/core_test/order.h>
#include <mu/core_test/segment.h>
#include <mu/core_test/apply.h>

void mu::core_test::tests::run ()
{
	{
		list test;
		test.run ();
	}
	{
		filesystem_test test;
		test.run ();
	}
/*	{
		directory_iterator_test test;
		test.run ();
    }*/
	{
		visitor test;
		test.run ();
	}
	{
		order test;
		test.run ();
	}
	{
		segment test;
		test.run ();
	}
	{
		apply test;
		test.run ();
	}
}
