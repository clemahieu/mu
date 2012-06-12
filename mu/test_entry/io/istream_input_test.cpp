#include <mu/io/lexer/istream_input.h>

#include <sstream>

#include <assert.h>

#include <gtest/gtest.h>

TEST (io_test, istream_input_test1)
{
	std::stringstream str ("");
	mu::io::lexer::istream_input input (str);
	wchar_t val (input ());
	assert (val == L'\uffff');
}