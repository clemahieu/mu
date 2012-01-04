#include "source_result.h"

void lambda_p_io_test::source_result::operator () (wchar_t char_a)
{
	results.push_back (char_a);
}