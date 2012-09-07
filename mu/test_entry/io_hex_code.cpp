#include <mu/test_entry/io_lexer_result.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/lexer_lexer.h>
#include <mu/io/source.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, hex_code1)
{
	mu::io_test::lexer_result result;
	mu::core::errors::error_list errors;
	mu::io::lexer::lexer lexer (errors,
                                [&result]
                                (mu::io::tokens::token const & token_a)
                                {
                                    result (token_a);
                                });
	mu::io::process (lexer, U":aq");
	EXPECT_EQ (result.results.empty (), true);
	EXPECT_EQ (!errors.errors.empty (), true);
}

TEST (io_test, hex_code2)
{
	mu::io_test::lexer_result result;
	mu::core::errors::error_list errors;
	mu::io::lexer::lexer lexer (errors,
                                [&result]
                                (mu::io::tokens::token const & token_a)
                                {
                                    result (token_a);
                                });
	mu::io::process (lexer, U":uq");
	EXPECT_EQ (result.results.empty (), true);
	EXPECT_EQ (!errors.errors.empty (), true);
}