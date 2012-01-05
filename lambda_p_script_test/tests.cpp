#include "tests.h"

#include <lambda_p_test/adata_test.h>
#include <lambda_p_test/apply_binder_test.h>
#include <lambda_p_test/bind_procedure_test_1.h>
#include <lambda_p_test/cvalue_test.h>
#include <lambda_p_test/list_test.h>
#include <lambda_p_test/loop_test.h>
#include <lambda_p_test/number_binder_test.h>
#include <lambda_p_test/package_test_1.h>
#include <lambda_p_test/routine_binder_test.h>
#include <lambda_p_test/times_test.h>
#include <lambda_p_test/unbindable_statement_test.h>
#include <lambda_p_test/routine_input_test_1.h>

void lambda_p_kernel_test::tests::run ()
{
	{
		adata_test test;
		test.run ();
	}
	{
		apply_binder_test test;
		test.run ();
	}
	{
		bind_procedure_test_1 test;
		test.run ();
	}
	{
		cvalue_test test;
		test.run ();
	}
	{
		list_test test;
		test.run ();
	}
	{
		loop_test test;
		test.run ();
	}
	{
		number_binder_test test;
		test.run ();
	}
	{
		package_test_1 test;
		test.run ();
	}
	{
		routine_binder_test test;
		test.run ();
	}
	{
		times_test test;
		test.run ();
	}
	{
		unbindable_statement_test test;
		test.run ();
	}
	{
		routine_input_test_1 test;
		test.run ();
	}
}