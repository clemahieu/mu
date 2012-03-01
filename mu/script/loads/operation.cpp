#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/load/operation.h>
#include <mu/script/cluster/node.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/string/node.h>

#include <boost/make_shared.hpp>

void mu::script::loads::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (parameters [0]));
	auto file (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [1]));
	if (extensions.get () != nullptr)
	{
		if (file.get () != nullptr)
		{
			mu::script::load::operation load;
			auto cluster (load.core (errors_a, extensions, file));
			if (!(*errors_a) ())
			{
				auto result (boost::make_shared <mu::script::extensions::node> ());
				for (auto i (cluster->names.begin ()), j (cluster->names.end ()); i != j; ++i)
				{
					result->extensions->extensions_m [i->first] = boost::make_shared <mu::io::analyzer::extensions::global> (i->second);
				}
				results.push_back (result);
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

size_t mu::script::loads::operation::count ()
{
	return 2;
}