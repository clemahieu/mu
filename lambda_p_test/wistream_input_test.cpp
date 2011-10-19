#include "wistream_input_test.h"

#include <lambda_p_repl/wistream_input.h>

#include <sstream>

#include <assert.h>

void lambda_p_test::wistream_input_test::run ()
{
	std::wstringstream stream (L"");
	lambda_p_repl::wistream_input input (stream);
	wchar_t val (input ());
	assert (val == L'\uffff');
}