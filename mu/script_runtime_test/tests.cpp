#include <mu/script_runtime_test/tests.h>

#include <mu/script_runtime_test/context.h>

void mu::script_runtime_test::tests::run ()
{
	{
		mu::script_runtime_test::context test;
		test.run ();
	}
}