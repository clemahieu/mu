#include <mu/core/errors/error_list.h>
#include <mu/script/builder.h>
#include <mu/io/source.h>
#include <mu/script/api.h>
#include <mu/script/parser_scope_node.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

TEST (script_test, string_extension1)
{
    auto core (mu::script::api::core ());
	mu::script::builder builder (core);
	mu::io::process (builder, U"[1 ; [`]]");
	EXPECT_TRUE (builder.errors.errors.empty ());
}

TEST (script_test, string_extension2)
{
    auto core (mu::script::api::core ());
	mu::script::builder builder (core);
	mu::io::process (builder, U"[1 ; [` ]]");
	EXPECT_TRUE (builder.errors.errors.empty ());
}

TEST (script_test, string_extension3)
{
    auto core (mu::script::api::core ());
	mu::script::builder builder (core);
	mu::io::process (builder, U"[1 ; [`a]]");
	EXPECT_TRUE (builder.errors.errors.empty ());
}