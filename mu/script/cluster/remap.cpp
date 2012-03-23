#include <mu/script/cluster/remap.h>

#include <mu/script/check.h>
#include <mu/script/context.h>
#include <mu/core/cluster.h>
#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/core/reference.h>

bool mu::script::cluster::remap::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::core::cluster> () (context_a));
	if (valid)
	{
		auto cluster (boost::static_pointer_cast <mu::core::cluster> (context_a.parameters (0)));
	}

	return valid;
}

void mu::script::cluster::remap::operator () (mu::core::cluster * cluster_a)
{
	for (auto i (cluster_a->routines.begin ()), j (cluster_a->routines.end ()); i != j; ++i)
	{
		(*(*i)) (this);
	}
}

void mu::script::cluster::remap::operator () (mu::core::expression * expression_a)
{
	for (auto i (expression_a->dependencies.begin ()), j (expression_a->dependencies.end ()); i != j; ++i)
	{
		auto existing (mapping.find (*i));
		if (existing != mapping.end ())
		{
			*i = existing->second;
		}
		(*(*i)) (this);
	}
}

void mu::script::cluster::remap::operator () (mu::core::parameters * parameters_a)
{
}

void mu::script::cluster::remap::operator () (mu::core::reference * reference_a)
{
	(*reference_a->expression) (this);
}

void mu::script::cluster::remap::operator () (mu::core::node * node_a)
{
}

void mu::script::cluster::remap::operator () (mu::core::routine * routine_a)
{
	(*routine_a->body) (this);
}
