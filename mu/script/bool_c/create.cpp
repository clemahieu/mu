#include "create.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/script/bool_c/node.h>

#include <sstream>

mu::script::bool_c::create::create ()
{
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"true"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (true))));
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"false"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (false))));
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"yes"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (true))));
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"no"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (false))));
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"1"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (true))));
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"0"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (false))));
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"on"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (true))));
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"off"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (false))));
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"high"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (true))));
	values.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (std::wstring (L"low"), boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (false))));
}

void mu::script::bool_c::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		std::wstring lower;
		std::transform (one->string.begin (), one->string.end (), lower.begin (), ::tolower);
		auto existing (values.find (lower));
		if (existing != values.end ())
		{
			results.push_back (existing->second);
		}
		else
		{
			std::wstringstream message;
			message << L"Cannot convert value: ";
			message << one->string;
			message << L" to a bool";
			(*errors_a) (message.str ());
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::script::bool_c::create::count ()
{
	return 1;
}

std::wstring mu::script::bool_c::create::name ()
{
	return std::wstring (L"mu::script::bool_c::create");
}