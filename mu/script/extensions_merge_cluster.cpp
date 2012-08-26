#include <mu/script/extensions/merge_cluster.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/extensions/node.h>
#include <mu/script/string/node.h>
#include <mu/script/cluster/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/check.h>

#include <sstream>

#include <boost/make_shared.hpp>

bool mu::script::extensions::merge_cluster::operator () (mu::script_runtime::context & context_a)
{	
	bool result (mu::script::check <mu::script::extensions::node, mu::script::string::node, mu::script::cluster::node> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::script::extensions::node> (context_a.parameters (0)));
		auto two (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters (1)));
		auto three (boost::static_pointer_cast <mu::script::cluster::node> (context_a.parameters (2)));
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
				context_a.errors (message.str ());
			}
		}
	}
	return result;
}

std::wstring mu::script::extensions::merge_cluster::name ()
{
	return std::wstring (L"mu::script::extensions::merge_cluster");
}