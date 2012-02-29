#include "merge.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/string/node.h>

#include <sstream>

void mu::script::extensions::merge::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::extensions::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [1]));
	auto three (boost::dynamic_pointer_cast <mu::script::extensions::node> (parameters [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (three.get () != nullptr)
			{
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
						(*errors_a) (message.str ());
					}
				}
			}
			else
			{
				invalid_type (errors_a, parameters [2], 2);
			}
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::script::extensions::merge::count ()
{
	return 3;
}

std::wstring mu::script::extensions::merge::name ()
{
	return std::wstring (L"mu::script::extensions::merge");
}