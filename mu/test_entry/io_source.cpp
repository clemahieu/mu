#include <mu/test_entry/io_source_result.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

TEST (io_test, source1)
{
	mu::io_test::source_result result;
	result (U'a');
	EXPECT_EQ (result.results.size (), 1);
	EXPECT_EQ (result.results [0], U'a');
}