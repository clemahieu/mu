#include <mu/io/keywording_keywording.h>
#include <mu/test_entry/io_lexer_result.h>
#include <mu/core/errors/error_list.h>
#include <mu/test_entry/io_extension1.h>
#include <mu/test_entry/io_extension2.h>
#include <mu/test_entry/io_extension3.h>
#include <mu/test_entry/io_extension4.h>
#include <mu/test_entry/io_extension5.h>
#include <mu/core/errors/error.h>
#include <mu/io/keywording_extensions.h>
#include <mu/io/tokens_identifier.h>

#include <boost/bind.hpp>

#include <map>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, extension1)
{
    mu::io::context context;
	mu::io_test::lexer_result result;
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension1> (mu::string (U"a")));
    ASSERT_TRUE (!failed);
	mu::io::keywording::keywording keywording (result.errors,
                                               [&result]
                                               (mu::io::tokens::token * token_a)
                                               {
                                                   result (token_a);
                                               }, extensions);
	keywording (new (GC) mu::io::tokens::identifier (context, mu::string (U"a")));
	EXPECT_TRUE (result.errors.errors.empty ());
	ASSERT_TRUE (result.results.size () == 0);
}

TEST (io_test, extension2)
{
    mu::io::context context;
	mu::io_test::lexer_result result;
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension2> (mu::string (U"a")));
    ASSERT_TRUE (!failed);
	mu::io::keywording::keywording keywording (result.errors,
                                               [&result]
                                               (mu::io::tokens::token * token_a)
                                               {
                                                   result (token_a);
                                               }, extensions);
	keywording (new (GC) mu::io::tokens::identifier (context, mu::string (U"a")));
	EXPECT_TRUE (result.errors.errors.empty ());
	EXPECT_TRUE (result.results.size () == 1);
}

TEST (io_test, extension3)
{
    mu::io::context context;
	mu::io_test::lexer_result result;
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension3> (mu::string (U"a")));
    ASSERT_TRUE (!failed);
	mu::io::keywording::keywording keywording (result.errors,
                                               [&result]
                                               (mu::io::tokens::token * token_a)
                                               {
                                                   result (token_a);
                                               }, extensions);
	keywording (new (GC) mu::io::tokens::identifier (context, mu::string (U"a")));
	EXPECT_TRUE (result.errors.errors.empty ());
	EXPECT_TRUE (result.results.size () == 2);
}

TEST (io_test, extension4)
{
    mu::io::context context;
	mu::io_test::lexer_result result;
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension4> (mu::string (U"a")));
    ASSERT_TRUE (!failed);
	mu::io::keywording::keywording keywording (result.errors,
                                               [&result]
                                               (mu::io::tokens::token * token_a)
                                               {
                                                   result (token_a);
                                               }, extensions);
	keywording (new (GC) mu::io::tokens::identifier (context, mu::string (U"a")));
	keywording (new (GC) mu::io::tokens::identifier (context, mu::string (U"b")));
	EXPECT_TRUE (result.errors.errors.empty ());
	EXPECT_TRUE (result.results.size () == 1);
}