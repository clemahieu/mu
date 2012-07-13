#include <mu/test_entry/io/source_result.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

TEST (io_test, source1)
{
	mu::io_test::source_result result;
	result (L'a');
	EXPECT_EQ (result.results.size (), 1);
	EXPECT_EQ (result.results [0], L'a');
}