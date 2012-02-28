#include "merge.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/extensions.h>

#include <sstream>

void mu::script::extensions::merge::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::extensions::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::extensions::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			for (auto i (two->extensions->extensions_m.begin ()), j (two->extensions->extensions_m.end ()); i != j; ++i)
			{
				auto existing (one->extensions->extensions_m.find (i->first));
				if (existing == one->extensions->extensions_m.end ())
				{
					two->extensions->extensions_m [i->first] = i->second;
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
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [1], 1);
	}
}

size_t mu::script::extensions::merge::count ()
{
	return 2;
}