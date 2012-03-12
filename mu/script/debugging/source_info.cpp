#include <mu/script/debugging/source_info.h>

mu::script::debugging::source_info::source_info (mu::core::context context_a)
	: context (context_a)
{
}

std::wstring mu::script::debugging::source_info::stacktrace_line ()
{
	return context.string ();
}