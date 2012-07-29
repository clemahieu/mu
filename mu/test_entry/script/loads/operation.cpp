#include <mu/core/errors/error_list.h>
#include <mu/script/loads/operation.h>
#include <mu/script/extensions/node.h>
#include <mu/script/string/node.h>
#include <mu/script/context.h>
#include <mu/io/keywording/extensions.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, loads1)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::loads::operation);
	//ctx.push (new (GC) mu::script::extensions::node);
	ctx.push (new (GC) mu::script::string::node (mu::string (U"source_test.mu")));
	auto valid (ctx ());
    ASSERT_TRUE (valid);
	ASSERT_TRUE (ctx.working_size () == 1);
	auto extensions (dynamic_cast <mu::script::extensions::node *> (ctx.working (0)));
	ASSERT_TRUE (extensions != nullptr);
	auto a ((*extensions->extensions) (mu::string (U"a")));
	EXPECT_TRUE (!a.empty ());
	auto b ((*extensions->extensions) (mu::string (U"b")));
	EXPECT_TRUE (!b.empty ());
}