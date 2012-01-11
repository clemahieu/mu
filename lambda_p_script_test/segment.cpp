#include "segment.h"

#include <lambda_p_script/segment.h>

#include <assert.h>

void lambda_p_script_test::segment::run ()
{
	run_1 ();
}

void lambda_p_script_test::segment::run_1 ()
{
	std::vector <size_t> values (5);
	for (size_t i (0), j (5); i != j; ++i)
	{
		values [i] = i;
	}
	lambda_p_script::segment <size_t> segment (1, 3, values);
	auto i (segment.begin ());
	assert (*i == 1);
	++i;
	assert (*i == 2);
	++i;
	assert (*i == 3);
	++i;
	assert (i == segment.end ());
	assert (segment [0] == 1);
	assert (segment [1] == 2);
	assert (segment [2] == 3);
}