#include <mu/core/errors/error_list.h>
#include <mu/script/loads/operation.h>
#include <mu/script/extensions/node.h>
#include <mu/script/string/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/context.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, loads1)
{
	mu::core::errors::errors errors (new (GC) mu::core::errors::error_list);
	mu::script::context ctx (errors);
	ctx.push (new (GC) mu::script::loads::operation);
	ctx.push (new (GC) mu::script::extensions::node);
	ctx.push (new (GC) mu::script::string::node (mu::string (U"source_test.mu")));
	auto valid (ctx ());
	errors.target->print (std::wcout);
    EXPECT_TRUE (valid);
	EXPECT_TRUE (ctx.working_size () == 1);
	auto extensions (dynamic_cast <mu::script::extensions::node *> (ctx.working (0)));
	EXPECT_TRUE (extensions != nullptr);
	auto a ((*extensions->extensions) (mu::string (U"a")));
	EXPECT_TRUE (a != nullptr);
	auto b ((*extensions->extensions) (mu::string (U"b")));
	EXPECT_TRUE (b != nullptr);
}