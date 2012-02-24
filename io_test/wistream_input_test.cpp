#include "wistream_input_test.h"

#include <io/lexer/wistream_input.h>

#include <sstream>

#include <assert.h>

void mu::io_test::wistream_input_test::run ()
{
	std::wstringstream stream (L"");
	mu::io::lexer::wistream_input input (stream);
	wchar_t val (input ());
	assert (val == L'\uffff');
}