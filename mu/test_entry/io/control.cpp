#include <mu/test_entry/io/lexer_result.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/source.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, control1)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":");
	lexer ();
	EXPECT_EQ (result.results.empty (), true);
	EXPECT_EQ (!errors->errors.empty (), true);
}

TEST (io_test, control2)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":0");
	lexer ();
	EXPECT_EQ (result.results.empty (), true);
	EXPECT_EQ (!errors->errors.empty (), true);
}