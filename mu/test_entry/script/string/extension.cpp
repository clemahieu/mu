#include <mu/core/errors/error_list.h>
#include <mu/io/builder.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/source.h>
#include <mu/script/api.h>
#include <mu/script/extensions/node.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

TEST (script_test, string_extension1)
{
	mu::io::builder builder (mu::script::api::core ()->extensions);
	builder (U"[` ;; 1]");
	builder ();
	EXPECT_EQ (!builder.errors->errors.empty (), true);
}

TEST (script_test, string_extension2)
{
	mu::io::builder builder (mu::script::api::core ()->extensions);
	builder (U"[`[] ;; 1]");
	builder ();
	EXPECT_EQ (!builder.errors->errors.empty (), true);
}

TEST (script_test, string_extension3)
{
	mu::io::builder builder (mu::script::api::core ()->extensions);
	builder (U"[` a ;; 1]");
	builder ();
	EXPECT_EQ (builder.errors->errors.empty (), true);
}