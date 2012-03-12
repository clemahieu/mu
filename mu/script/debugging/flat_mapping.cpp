#include <mu/script/debugging/flat_mapping.h>

#include <mu/script/debugging/string_info.h>

#include <sstream>

#include <boost/make_shared.hpp>

boost::shared_ptr <mu::script::debugging::operation_info> mu::script::debugging::flat_mapping::operation_info (boost::shared_ptr <mu::script::operation> operation_a)
{
	boost::shared_ptr <mu::script::debugging::operation_info> result;
	auto existing (map.find (operation_a));
	if (existing != map.end ())
	{
		result = existing->second;
	}
	else
	{
		result = boost::make_shared <mu::script::debugging::string_info> (std::wstring (L"(Unknown location)"));
	}
	return result;
}