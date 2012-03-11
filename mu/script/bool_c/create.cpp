#include <mu/script/bool_c/create.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

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

void mu::script::bool_c::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::string::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters [0]));
		std::wstring lower;
		std::transform (one->string.begin (), one->string.end (), lower.begin (), ::tolower);
		auto existing (values.find (lower));
		if (existing != values.end ())
		{
			context_a.results.push_back (existing->second);
		}
		else
		{
			std::wstringstream message;
			message << L"Cannot convert value: ";
			message << one->string;
			message << L" to a bool";
			context_a (message.str ());
		}
	}
}

std::wstring mu::script::bool_c::create::name ()
{
	return std::wstring (L"mu::script::bool_c::create");
}