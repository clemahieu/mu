#include "segment.h"

#include <mu/core/segment.h>

#include <assert.h>

void lambda_p_test::segment::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::segment::run_1 ()
{
	std::vector <size_t> values (5);
	for (size_t i (0), j (5); i != j; ++i)
	{
		values [i] = i;
	}
	mu::core::segment <size_t> segment (1, values);
	auto i (segment.begin ());
	assert (*i == 1);
	++i;
	assert (*i == 2);
	++i;
	assert (*i == 3);
	++i;
	assert (*i == 4);
	++i;
	assert (i == segment.end ());
	assert (segment [0] == 1);
	assert (segment [1] == 2);
	assert (segment [2] == 3);
	assert (segment [3] == 4);
	assert (segment.size () == 4);
}

void lambda_p_test::segment::run_2 ()
{
	std::vector <size_t> values (5);
	mu::core::segment <size_t> segment (values);
	for (auto i (segment.begin ()), j (segment.end ()); i != j; ++i)
	{
		auto val (*i);
	}
}