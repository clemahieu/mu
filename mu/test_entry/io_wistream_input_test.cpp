#include <mu/io/lexer_wistream_input.h>

#include <sstream>

#include <assert.h>

#include <gtest/gtest.h>

TEST (io_test, wistream_input_test1)
{
	std::wstringstream stream (L"");
	mu::io::lexer::wistream_input input (stream);
	wchar_t val (input ());
	EXPECT_EQ (val, L'\uffff');
}