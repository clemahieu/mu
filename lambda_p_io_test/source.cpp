#include "source.h"

#include <lambda_p_io/source.h>
#include <lambda_p_io_test/source_result.h>

#include <boost/bind.hpp>

void lambda_p_io_test::source::run ()
{
	run_1 ();
}

void lambda_p_io_test::source::run_1 ()
{
	lambda_p_io_test::source_result result;
	lambda_p_io::source source (boost::bind (&lambda_p_io_test::source_result::operator(), &result, _1));
	source (L'a');
	assert (result.results.size () == 1);
	assert (result.results [0] == L'a');
}