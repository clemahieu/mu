#include <mu/script/loads/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/load/operation.h>
#include <mu/script/cluster/node.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/string/node.h>
#include <mu/core/cluster.h>
#include <mu/script/analyzer/operation.h>
#include <mu/script/check.h>
#include <mu/core/routine.h>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

bool mu::script::loads::operation::operator () (mu::script::context & context_a)
{
	bool complete (mu::script::check <mu::script::extensions::node, mu::script::string::node> () (context_a));
	if (complete)
	{
		auto extensions (boost::static_pointer_cast <mu::script::extensions::node> (context_a.parameters (0)));
		auto file (boost::static_pointer_cast <mu::script::string::node> (context_a.parameters (1)));
		auto result (core (context_a, extensions, file));
		if (result.get () != nullptr)
		{
			context_a.push (result);
		}
	}
	return complete;
}

boost::shared_ptr <mu::script::extensions::node> mu::script::loads::operation::core (mu::script::context & context_a, boost::shared_ptr <mu::script::extensions::node> extensions, boost::shared_ptr <mu::script::string::node> file)
{
	auto result (boost::make_shared <mu::script::extensions::node> ());
	mu::script::load::operation load;
	auto ast (load.core (context_a, file));
	if (!context_a ())
	{
		mu::script::analyzer::operation analyzer;
		auto cluster (analyzer.core (context_a, extensions, ast));
		if (cluster.get () != nullptr)
		{
			for (auto i (cluster->names.begin ()), j (cluster->names.end ()); i != j; ++i)
			{
				result->extensions->extensions_m [i->first] = boost::make_shared <mu::io::analyzer::extensions::global> (i->second);
			}
		}
	}
	return result;
}