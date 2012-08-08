#include <mu/script/cluster/remap.h>

#include <mu/core/check.h>
#include <mu/script/context.h>
#include <mu/core/cluster.h>
#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/core/reference.h>

#include <gc_cpp.h>

#include <assert.h>

bool mu::script::cluster::remap::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::core::cluster> (context_a));
	if (valid)
	{
		auto cluster (static_cast <mu::core::cluster *> (context_a.parameters (0)));
		auto cluster_target (new (GC) mu::core::cluster);
		(*this) (cluster, cluster_target);
		context_a.push (cluster_target);
	}
	return valid;
}

void mu::script::cluster::remap::operator () (mu::core::cluster * source, mu::core::cluster * target)
{
	for (auto i (source->routines.begin ()), j (source->routines.end ()); i != j; ++i)
	{
		auto routine (new (GC) mu::core::routine);
		target->routines.push_back (routine);
		(*this) (*i, routine);
	}
}

void mu::script::cluster::remap::operator () (mu::core::routine * source, mu::core::routine * target)
{
	auto expression (new (GC) mu::core::expression);
	target->body = expression;
	(*this) (source->body, expression);
}

void mu::script::cluster::remap::operator () (mu::core::expression * source, mu::core::expression * target)
{
	for (auto i (source->dependencies.begin ()), j (source->dependencies.end ()); i != j; ++i)
	{
		auto value ((*this) (*i));
		assert (value != nullptr);
		auto reference (dynamic_cast <mu::core::reference *> (value));
		auto expression (dynamic_cast <mu::core::expression *> (value));
		auto routine (dynamic_cast <mu::core::routine *> (value));
		if (reference != nullptr)
		{
			auto reference_l (new (GC) mu::core::reference);
			reference_l->index = reference->index;
			target->dependencies.push_back (reference_l);
			(*this) (reference, reference_l);
		}
		else if (expression != nullptr)
		{
			auto expression_l (new (GC) mu::core::expression);
			target->dependencies.push_back (expression_l);
			(*this) (expression, expression_l);
		}
		else if (routine != nullptr)
		{
			target->dependencies.push_back (value);
		}
		else
		{
			target->dependencies.push_back (value);
		}
	}
}

void mu::script::cluster::remap::operator () (mu::core::reference * source, mu::core::reference * target)
{
	auto expression (new (GC) mu::core::expression);
	target->expression = expression;
	(*this) (source->expression, target->expression);
}