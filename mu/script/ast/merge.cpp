#include "merge.h"

#include <mu/io/ast/cluster.h>

#include <boost/make_shared.hpp>

void mu::script::ast::merge::perform (mu::script::context & context_a)
{
	auto result (boost::make_shared <mu::io::ast::cluster> ());
	size_t position (0);
	for (auto i (context_a.parameters.begin ()), j (context_a.parameters.end ()); i != j; ++i, ++position)
	{
		auto cluster (boost::dynamic_pointer_cast <mu::io::ast::cluster> (*i));
		if (cluster.get () != nullptr)
		{
			result->expressions.insert (result->expressions.end (), cluster->expressions.begin (), cluster->expressions.end ());
		}
		else
		{
			invalid_type (context_a.errors, *i, position);
		}
	}
}