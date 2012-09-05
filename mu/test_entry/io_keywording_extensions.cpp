#include <mu/io/analyzer_extensions.h>
#include <mu/test_entry/io_extension1.h>
#include <mu/test_entry/io_extension5.h>
#include <mu/core/node.h>

#include <gc_cpp.h>

#include <gtest/gtest.h>

// Check that an extension can't collide
TEST (io_test, keywording_extensions1)
{
	mu::io::keywording::extensions extensions;
	auto failed (extensions (mu::string (U"a"), new (GC) mu::core::node));
    EXPECT_TRUE (!failed);
    auto failed2 (extensions (mu::string (U"a"), new (GC) mu::core::node));
    EXPECT_TRUE (failed2);
}

// Check that an extension can't be dominated by another
TEST (io_test, keywording_extensions2)
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
TEST (io_test, keywording_extensions3)
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
TEST (io_test, keywording_extensions4)
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
TEST (io_test, keywording_extensions5)
{
	auto extensions (new (GC) mu::io::keywording::extensions);
	auto failed (extensions->add <mu::io_test::extension5> (mu::string (U"a")));
    EXPECT_TRUE (!failed);
    auto exists ((*extensions) (mu::string (U"ab")));
    EXPECT_TRUE (!boost::get <0> (exists).empty ());
}