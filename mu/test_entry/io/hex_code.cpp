#include <mu/test_entry/io/lexer_result.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/source.h>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, hex_code1)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":aq");
	lexer ();
	EXPECT_EQ (result.results.empty (), true);
	EXPECT_EQ (!errors->errors.empty (), true);
}

TEST (io_test, hex_code2)
{
	mu::io_test::lexer_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io_test::lexer_result::operator (), &result, _1, _2));
	lexer (L":uq");
	lexer ();
	EXPECT_EQ (result.results.empty (), true);
	EXPECT_EQ (!errors->errors.empty (), true);
}