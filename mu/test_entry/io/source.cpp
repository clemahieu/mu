#include <mu/test_entry/io/source_result.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

TEST (io_test, source1)
{
	mu::io_test::source_result result;
	result (L'a');
	assert (result.results.size () == 1);
	assert (result.results [0] == L'a');
}