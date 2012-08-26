#include <mu/test_entry/io_source_result.h>

void mu::io_test::source_result::operator () (char32_t char_a)
{
	results.push_back (char_a);
}