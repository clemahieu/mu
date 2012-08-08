#include <mu/script/loads/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/load/operation.h>
#include <mu/script/extensions/node.h>
#include <mu/script/string/node.h>
#include <mu/core/cluster.h>
#include <mu/script/analyzer/operation.h>
#include <mu/core/check.h>
#include <mu/core/routine.h>
#include <mu/io/keywording/extensions.h>
#include <mu/script/context.h>

#include <boost/bind.hpp>

#include <gc_cpp.h>

bool mu::script::loads::operation::operator () (mu::script::context & context_a)
{
	bool complete (mu::core::check <mu::script::string::node> (context_a));
	if (complete)
	{
		auto file (static_cast <mu::script::string::node *> (context_a.parameters (0)));
		auto result (core (context_a, file));
		if (result != nullptr)
		{
			context_a.push (result);
		}
	}
	return complete;
}

mu::script::extensions::node * mu::script::loads::operation::core (mu::script::context & context_a, mu::script::string::node * file)
{
	auto result (new (GC) mu::script::extensions::node);
	mu::script::load::operation load;
	auto ast (load.core (context_a, file));
	if (ast != nullptr)
	{
		mu::script::analyzer::operation analyzer;
		auto cluster (analyzer.core (context_a, ast));
		if (cluster != nullptr)
		{
			for (auto i (cluster->names.begin ()), j (cluster->names.end ()); i != j; ++i)
			{
				(*result->extensions) (i->first, i->second);
			}
		}
	}
	return result;
}