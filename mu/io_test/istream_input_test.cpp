#include "istream_input_test.h"

#include <mu/io/lexer.istream_input.h>

#include <sstream>

#include <assert.h>

void mu::io_test::istream_input_test::run ()
{
	std::stringstream str ("");
	mu::io::lexer::istream_input input (str);
	wchar_t val (input ());
	assert (val == L'\uffff');
}
