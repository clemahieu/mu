#include "source.h"

#include <mu/io/source.h>
#include <mu/io_test/source_result.h>

#include <boost/bind.hpp>

void mu::io_test::source::run ()
{
	run_1 ();
}

void mu::io_test::source::run_1 ()
{
	mu::io_test::source_result result;
	mu::io::source source (boost::bind (&mu::io_test::source_result::operator(), &result, _1));
	source (L'a');
	assert (result.results.size () == 1);
	assert (result.results [0] == L'a');
}