#include <mu/script/loads.operation.h>

#include <mu/core/errors.error_target.h>
#include <mu/script/load.operation.h>
#include <mu/script/cluster.node.h>
#include <mu/script/extensions.node.h>
#include <mu/io/analyzer.extensions.global.h>
#include <mu/io/analyzer.extensions.extensions.h>
#include <mu/script/runtime.routine.h>
#include <mu/script/string.node.h>
#include <mu/script_io/builder.h>
#include <mu/script_io/cluster.h>
#include <mu/script/analyzer.operation.h>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

void mu::script::loads::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (parameters [0]));
	auto file (boost::dynamic_pointer_cast <mu::script::string::node> (parameters [1]));
	if (extensions.get () != nullptr)
	{
		if (file.get () != nullptr)
		{
			auto result (core (errors_a, extensions, file));
			if (result.get () != nullptr)
			{
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

boost::shared_ptr <mu::script::extensions::node> mu::script::loads::operation::core (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::script::extensions::node> extensions, boost::shared_ptr <mu::script::string::node> file)
{
	auto result (boost::make_shared <mu::script::extensions::node> ());
	mu::script::load::operation load;
	auto ast (load.core (errors_a, file));
	if (!(*errors_a) ())
	{
		mu::script::analyzer::operation analyzer;
		auto cluster (analyzer.core (errors_a, extensions, ast));
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

size_t mu::script::loads::operation::count ()
{
	return 2;
}
