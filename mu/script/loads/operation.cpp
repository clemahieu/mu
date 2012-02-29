#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/load/operation.h>
#include <mu/script/cluster/node.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/runtime/routine.h>

#include <boost/make_shared.hpp>

void mu::script::loads::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	mu::script::load::operation load;
	std::vector <boost::shared_ptr <mu::core::node>> r1;
	load.perform (errors_a, parameters, r1);
	if (!(*errors_a) ())
	{
		auto result (boost::make_shared <mu::script::extensions::node> ());
		auto cluster (boost::static_pointer_cast <mu::script::cluster::node> (r1 [0]));
		for (auto i (cluster->names.begin ()), j (cluster->names.end ()); i != j; ++i)
		{
			result->extensions->extensions_m [i->first] = boost::make_shared <mu::io::analyzer::extensions::global> (i->second);
		}
		results.push_back (result);
	}
}

size_t mu::script::loads::operation::count ()
{
	return 2;
}