#include <mu/core/errors/error_list.h>
#include <mu/script/builder.h>
#include <mu/io/source.h>
#include <mu/script/api.h>
#include <mu/script/extensions_node.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

TEST (script_test, string_extension1)
{
	mu::script::builder builder (mu::script::api::core ()->extensions);
	mu::io::process (builder, U"[1 ; [`]]");
	EXPECT_TRUE (builder.errors.errors.empty ());
}

TEST (script_test, string_extension2)
{
	mu::script::builder builder (mu::script::api::core ()->extensions);
	mu::io::process (builder, U"[1 ; [` ]]");
	EXPECT_TRUE (builder.errors.errors.empty ());
}

TEST (script_test, string_extension3)
{
	mu::script::builder builder (mu::script::api::core ()->extensions);
	mu::io::process (builder, U"[1 ; [`a]]");
	EXPECT_TRUE (builder.errors.errors.empty ());
}