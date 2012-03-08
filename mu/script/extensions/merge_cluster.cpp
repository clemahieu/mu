#include "merge_cluster.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/extensions/node.h>
#include <mu/script/string/node.h>
#include <mu/script/cluster/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/runtime/routine.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::script::extensions::merge_cluster::operator () (mu::script::context & context_a)
{	
	auto one (boost::dynamic_pointer_cast <mu::script::extensions::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::string::node> (context_a.parameters [1]));
	auto three (boost::dynamic_pointer_cast <mu::script::cluster::node> (context_a.parameters [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (three.get () != nullptr)
			{
				for (auto i (three->names.begin ()), j (three->names.end ()); i != j; ++i)
				{
					std::wstring name (two->string.begin (), two->string.end ());
					name.append (i->first);
					auto existing (one->extensions->extensions_m.find (name));
					if (existing == one->extensions->extensions_m.end ())
					{
						one->extensions->extensions_m [name] = boost::make_shared <mu::io::analyzer::extensions::global> (i->second);
					}
					else
					{
						std::wstringstream message;
						message << L"Extensions already has an extension named: ";
						message << name;
						(*context_a.errors) (message.str ());
					}
				}
			}
			else
			{
				invalid_type (context_a.errors, context_a.parameters [2], 2);
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::script::extensions::merge_cluster::count ()
{
	return 3;
}

std::wstring mu::script::extensions::merge_cluster::name ()
{
	return std::wstring (L"mu::script::extensions::merge_cluster");
}