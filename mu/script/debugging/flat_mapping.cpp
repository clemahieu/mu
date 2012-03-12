#include <mu/script/debugging/flat_mapping.h>

#include <sstream>

std::wstring mu::script::debugging::flat_mapping::stacktrace (boost::shared_ptr <mu::script::operation> operation_a)
{
	std::wstringstream result;
	auto existing (map.find (operation_a));
	if (existing != map.end ())
	{
		result << existing->second;
	}
	else
	{
		result << L"(Unknown location)";
	}
	return result.str ();
}