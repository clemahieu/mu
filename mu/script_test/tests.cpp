#include "tests.h"

#include <mu/script_test/routine.h>
#include <mu/script_test/call.h>
#include <mu/script_test/constant.h>
#include <mu/script_test/expression.h>
#include <mu/script_test/reference.h>
#include <mu/script_test/integer/equal.h>
#include <mu/script_test/closure/operation.h>
#include <mu/script_test/package/create.h>
#include <mu/script_test/package/get.h>
#include <mu/script_test/closure/apply.h>
#include <mu/script_test/times/operation.h>
#include <mu/script_test/closure/single.h>
#include <mu/script_test/package/get_recursive.h>
#include <mu/script_test/chain/operation.h>
#include <mu/script_test/string/extension.h>
#include <mu/script_test/cluster/get.h>
#include <mu/script_test/ast/extension.h>
#include <mu/script_test/cluster/node.h>
#include <mu/script_test/loadb/operation.h>

void mu::script_test::tests::run ()
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
		mu::script_test::integer::equal test;
		test.run ();
	}
	{
		mu::script_test::closure::operation test;
		test.run ();
	}
	{
		mu::script_test::package::create test;
		test.run ();
	}
	{
		mu::script_test::package::get test;
		test.run ();
	}
	{
		mu::script_test::closure::apply test;
		test.run ();
	}
	{
		mu::script_test::times::operation test;
		test.run ();
	}
	{
		mu::script_test::closure::single test;
		test.run ();
	}
	{
		mu::script_test::package::get_recursive test;
		test.run ();
	}
	{
		mu::script_test::chain::operation test;
		test.run ();
	}
	{
		mu::script_test::string::extension test;
		test.run ();
	}
	{
		mu::script_test::cluster::node test;
		test.run ();
	}
	{
		mu::script_test::cluster::get test;
		test.run ();
	}
	{
		mu::script_test::ast::extension test;
		test.run ();
	}
	{
		mu::script_test::loadb::operation test;
		test.run ();
	}
}