#include <mu/script_test/tests.h>

#include <mu/script_test/context.h>
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
#include <mu/script_test/ast/extension.h>
#include <mu/script_test/loadb/operation.h>
#include <mu/script_test/loads/operation.h>
#include <mu/script_test/analyzer/operation.h>
#include <mu/script_test/type_check/operation.h>
#include <mu/script_test/routine/node.h>

void mu::script_test::tests::run ()
{
	{
		mu::script_test::context test;
		test.run ();
	}
	{
		mu::script_test::type_check::operation test;
		test.run ();
	}
	{
		mu::script_test::routine::node test;
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
		mu::script_test::ast::extension test;
		test.run ();
	}
	{
		mu::script_test::analyzer::operation test;
		test.run ();
	}
	{
		mu::script_test::loadb::operation test;
		test.run ();
	}
	{
		mu::script_test::loads::operation test;
		test.run ();
	}
}