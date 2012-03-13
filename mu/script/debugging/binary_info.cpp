#include <mu/script/debugging/binary_info.h>

#include <typeinfo>

mu::script::debugging::binary_info::binary_info (std::type_info const & type_a)
	: type (type_a)
{
}

std::wstring mu::script::debugging::binary_info::stacktrace_line ()
{
	auto name (std::string (type.name ()));	
	return std::wstring (name.begin (), name.end ());
}