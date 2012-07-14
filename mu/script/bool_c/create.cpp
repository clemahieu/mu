#include <mu/script/bool_c/create.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

#include <sstream>

#include <gc_cpp.h>

mu::script::bool_c::create::create ()
{
	values [std::wstring (L"true")] = new (GC) mu::script::bool_c::node (true);
	values [std::wstring (L"false")] = new (GC) mu::script::bool_c::node (false);
	values [std::wstring (L"yes")] = new (GC) mu::script::bool_c::node (true);
	values [std::wstring (L"no")] = new (GC) mu::script::bool_c::node (false);
	values [std::wstring (L"1")] = new (GC) mu::script::bool_c::node (true);
	values [std::wstring (L"0")] = new (GC) mu::script::bool_c::node (false);
	values [std::wstring (L"on")] = new (GC) mu::script::bool_c::node (true);
	values [std::wstring (L"off")] = new (GC) mu::script::bool_c::node (false);
	values [std::wstring (L"high")] = new (GC) mu::script::bool_c::node (true);
	values [std::wstring (L"low")] = new (GC) mu::script::bool_c::node (false);
}

bool mu::script::bool_c::create::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::string::node> () (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::string::node *> (context_a.parameters (0)));
		std::wstring lower;
		std::transform (one->string.begin (), one->string.end (), lower.begin (), ::tolower);
		auto existing (values.find (lower));
		if (existing != values.end ())
		{
			context_a.push (existing->second);
		}
		else
		{
			std::wstringstream message;
			message << L"Cannot convert value: ";
			message << one->string;
			message << L" to a bool";
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}

std::wstring mu::script::bool_c::create::name ()
{
	return std::wstring (L"mu::script::bool_c::create");
}