#include <mu/io/keywording/keywording.h>
#include <mu/test_entry/io/lexer_result.h>
#include <mu/core/errors/error_list.h>
#include <mu/test_entry/io/extension1.h>
#include <mu/test_entry/io/extension2.h>
#include <mu/test_entry/io/extension3.h>
#include <mu/test_entry/io/extension4.h>
#include <mu/test_entry/io/extension5.h>
#include <mu/io/ast/cluster.h>
#include <mu/core/errors/error.h>
#include <mu/io/keywording/extensions.h>
#include <mu/io/tokens/identifier.h>

#include <boost/bind.hpp>

#include <map>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (io_test, extension1)
{	
	mu::io_test::lexer_result result;
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension1> (mu::string (U"a")));
    ASSERT_TRUE (!failed);
	mu::io::keywording::keywording keywording (result.errors, [&result] (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) {result (token_a, context_a);}, extensions);
	keywording (new (GC) mu::io::tokens::identifier (mu::string (U"a")), mu::io::debugging::context ());
	EXPECT_TRUE (result.errors.errors.empty ());
	ASSERT_TRUE (result.results.size () == 0);
}

TEST (io_test, extension2)
{	
	mu::io_test::lexer_result result;
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension2> (mu::string (U"a")));
    ASSERT_TRUE (!failed);
	mu::io::keywording::keywording keywording (result.errors, [&result] (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) {result (token_a, context_a);}, extensions);
	keywording (new (GC) mu::io::tokens::identifier (mu::string (U"a")), mu::io::debugging::context ());
	EXPECT_TRUE (result.errors.errors.empty ());
	EXPECT_TRUE (result.results.size () == 1);
}

TEST (io_test, extension3)
{	
	mu::io_test::lexer_result result;
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension3> (mu::string (U"a")));
    ASSERT_TRUE (!failed);
	mu::io::keywording::keywording keywording (result.errors, [&result] (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) {result (token_a, context_a);}, extensions);
	keywording (new (GC) mu::io::tokens::identifier (mu::string (U"a")), mu::io::debugging::context ());
	EXPECT_TRUE (result.errors.errors.empty ());
	EXPECT_TRUE (result.results.size () == 2);
}

TEST (io_test, extension4)
{	
	mu::io_test::lexer_result result;
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension4> (mu::string (U"a")));
    ASSERT_TRUE (!failed);
	mu::io::keywording::keywording keywording (result.errors, [&result] (mu::io::tokens::token * token_a, mu::io::debugging::context context_a) {result (token_a, context_a);}, extensions);
	keywording (new (GC) mu::io::tokens::identifier (mu::string (U"a")), mu::io::debugging::context ());
	keywording (new (GC) mu::io::tokens::identifier (mu::string (U"b")), mu::io::debugging::context ());
	EXPECT_TRUE (result.errors.errors.empty ());
	EXPECT_TRUE (result.results.size () == 1);
}

// Check that an extension can't be dominated by another
TEST (io_test, extension5)
{
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension5> (mu::string (U"a")));
    EXPECT_TRUE (!failed);
    auto failed2 (extensions->add <mu::io_test::extension5> (mu::string (U"ab")));
    EXPECT_TRUE (failed2);
    auto exists ((*extensions) (mu::string (U"ab")));
    EXPECT_TRUE (!boost::get <0> (exists).empty ());
}

// Check that an owning extension can't be inserted that would dominate other extensions
TEST (io_test, extension6)
{
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension5> (mu::string (U"ab")));
    EXPECT_TRUE (!failed);
    auto failed2 (extensions->add <mu::io_test::extension5> (mu::string (U"a")));
    EXPECT_TRUE (failed2);
    auto exists ((*extensions) (mu::string (U"a")));
    EXPECT_TRUE (boost::get <0> (exists).empty ());
}

// Check that an extension can be inserted dominated by a non-owning extension
TEST (io_test, extension7)
{
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension5> (mu::string (U"ab")));
    EXPECT_TRUE (!failed);
    auto failed2 (extensions->add <mu::io_test::extension1> (mu::string (U"a")));
    EXPECT_TRUE (!failed2);
    auto exists ((*extensions) (mu::string (U"a")));
    EXPECT_TRUE (!boost::get <0> (exists).empty ());
}

// Check dominating extension retrieval
TEST (io_test, extension8)
{
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension5> (mu::string (U"a")));
    EXPECT_TRUE (!failed);
    auto exists ((*extensions) (mu::string (U"ab")));
    EXPECT_TRUE (!boost::get <0> (exists).empty ());
}