#include "istream_input_test.h"

#include <lambda_p_io/lexer/istream_input.h>

#include <sstream>

#include <assert.h>

void lambda_p_io_test::istream_input_test::run ()
{
	std::stringstream str ("");
	lambda_p_io::lexer::istream_input input (str);
	wchar_t val (input ());
	assert (val == L'\uffff');
}