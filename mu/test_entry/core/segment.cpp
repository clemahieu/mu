#include <mu/core/segment.h>

#include <gtest/gtest.h>

TEST (core_test, segment1)
{
	std::vector <size_t> values (5);
	for (size_t i (0), j (5); i != j; ++i)
	{
		values [i] = i;
	}
	mu::core::segment <size_t> segment (1, values);
	auto i (segment.begin ());
	EXPECT_EQ (*i, 1);
	++i;
	EXPECT_EQ (*i, 2);
	++i;
	EXPECT_EQ (*i, 3);
	++i;
	EXPECT_EQ (*i, 4);
	++i;
	EXPECT_EQ (i, segment.end ());
	EXPECT_EQ (segment [0], 1);
	EXPECT_EQ (segment [1], 2);
	EXPECT_EQ (segment [2], 3);
	EXPECT_EQ (segment [3], 4);
	EXPECT_EQ (segment.size (), 4);
}

TEST (core_test, segment2)
{
	std::vector <size_t> values (5);
	mu::core::segment <size_t> segment (values);
	for (auto i (segment.begin ()), j (segment.end ()); i != j; ++i)
	{
		auto val (*i);
	}
}