#include <mu/core/errors/errors.h>
#include <mu/script/package/get_recursive.h>
#include <mu/script/package/node.h>
#include <mu/script/string/node.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, package_get_recursive1)
{
	auto package (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::package::get_recursive> ());
	ctx.push (package);
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), package);
}

TEST (script_test, package_get_recursive2)
{
	auto package (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	package->items [std::wstring (L"a")] = n1;
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::package::get_recursive> ());
	ctx.push (package);
	ctx.push (boost::shared_ptr <mu::core::node> (new mu::script::string::node (std::wstring (L"a"))));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), n1);
}

TEST (script_test, package_get_recursive3)
{
	auto package (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	auto package1 (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	auto n1 (boost::shared_ptr <mu::core::node> (new mu::core::node));
	package->items [std::wstring (L"a")] = package1;
	package1->items [std::wstring (L"b")] = n1;
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (boost::make_shared <mu::script::package::get_recursive> ());
	ctx.push (package);
	ctx.push (boost::shared_ptr <mu::core::node> (new mu::script::string::node (std::wstring (L"a"))));
	ctx.push (boost::shared_ptr <mu::core::node> (new mu::script::string::node (std::wstring (L"b"))));
	auto valid (ctx ());
	EXPECT_EQ (valid, true);
	EXPECT_EQ (ctx.working_size (), 1);
	EXPECT_EQ (ctx.working (0), n1);
}