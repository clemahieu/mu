#include <mu/test_entry/io/parser_result.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/parser/parser.h>
#include <mu/io/lexer/lexer.h>
#include <mu/io/source.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, single1)
{
	mu::io_test::parser_result result;
	auto errors (new (GC) mu::core::errors::error_list);
	mu::io::parser::parser parser (errors, boost::bind (&mu::io_test::parser_result::operator(), &result, _1));
	mu::io::lexer::lexer lexer (errors, boost::bind (&mu::io::parser::parser::operator (), &parser, _1, _2));
	mu::io::process (lexer, U" [     thing; :~");
	EXPECT_EQ (result.results.empty (), true);
	EXPECT_EQ (!errors->errors.empty (), true);
}