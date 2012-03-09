#include "merge.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/string/node.h>
#include <mu/script/check.h>

#include <sstream>

void mu::script::extensions::merge::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::extensions::node, mu::script::string::node, mu::script::extensions::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::extensions::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
		auto three (boost::static_pointer_cast <mu::script::extensions::node> (context_a.parameters [2]));
		for (auto i (three->extensions->extensions_m.begin ()), j (three->extensions->extensions_m.end ()); i != j; ++i)
		{
			std::wstring name (two->string.begin (), two->string.end ());
			name.append (i->first);
			auto existing (one->extensions->extensions_m.find (name));
			if (existing == one->extensions->extensions_m.end ())
			{
				one->extensions->extensions_m [name] = i->second;
			}
			else
			{
				std::wstringstream message;
				message << L"Extensions already contains extension named: ";
				message << i->first;
				(*context_a.errors) (message.str ());
			}
		}
	}
}

std::wstring mu::script::extensions::merge::name ()
{
	return std::wstring (L"mu::script::extensions::merge");
}