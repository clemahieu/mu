#include <mu/script/debugging/string_info.h>

mu::script::debugging::string_info::string_info (std::wstring string_a)
	: string (string_a)
{
}

std::wstring mu::script::debugging::string_info::stacktrace_line ()
{
	return string;
}