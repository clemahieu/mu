#include "tests.h"

#include <lambda_p_script_test/routine.h>
#include <lambda_p_script_test/call.h>
#include <lambda_p_script_test/constant.h>
#include <lambda_p_script_test/expression.h>
#include <lambda_p_script_test/reference.h>
#include <lambda_p_script_test/integer/equal.h>
#include <lambda_p_script_test/closure/operation.h>
#include <lambda_p_script_test/package/create.h>
#include <lambda_p_script_test/package/get.h>
#include <lambda_p_script_test/closure/apply.h>
#include <lambda_p_script_test/times/operation.h>
#include <lambda_p_script_test/closure/single.h>
#include <lambda_p_script_test/package/get_recursive.h>
#include <lambda_p_script_test/chain/operation.h>
#include <lambda_p_script_test/string/extension.h>
#include <lambda_p_script_test/analyzer/analyzer.h>
#include <lambda_p_script_test/cluster/get.h>
#include <lambda_p_script_test/ast/extension.h>
#include <lambda_p_script_test/remapping.h>

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
	{
		remapping test;
		test.run ();
	}
	{
		lambda_p_script_test::integer::equal test;
		test.run ();
	}
	{
		lambda_p_script_test::closure::operation test;
		test.run ();
	}
	{
		lambda_p_script_test::package::create test;
		test.run ();
	}
	{
		lambda_p_script_test::package::get test;
		test.run ();
	}
	{
		lambda_p_script_test::closure::apply test;
		test.run ();
	}
	{
		lambda_p_script_test::times::operation test;
		test.run ();
	}
	{
		lambda_p_script_test::closure::single test;
		test.run ();
	}
	{
		lambda_p_script_test::package::get_recursive test;
		test.run ();
	}
	{
		lambda_p_script_test::chain::operation test;
		test.run ();
	}
	{
		lambda_p_script_test::string::extension test;
		test.run ();
	}
	{
		lambda_p_script_test::analyzer::analyzer test;
		test.run ();
	}
	{
		lambda_p_script_test::cluster::get test;
		test.run ();
	}
	{
		lambda_p_script_test::ast::extension test;
		test.run ();
	}
}