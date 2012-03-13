#include <mu/script/debugging/flat_mapping.h>

#include <mu/script/debugging/string_info.h>
#include <mu/script/debugging/binary_info.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/operation.h>

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

void mu::script::debugging::flat_mapping::add_with_extensions (mu::script::extensions::node * extensions_a, std::wstring name, boost::shared_ptr <mu::script::operation> operation_a)
{
	extensions_a->extensions->extensions_m [name] = boost::make_shared <mu::io::analyzer::extensions::global> (operation_a);
	map [operation_a] = boost::make_shared <mu::script::debugging::binary_info> (typeid (*operation_a));
}