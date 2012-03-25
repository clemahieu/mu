#include <mu/script/cluster/remap.h>

#include <mu/script/check.h>
#include <mu/script/context.h>
#include <mu/core/cluster.h>
#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/core/reference.h>

#include <boost/make_shared.hpp>

bool mu::script::cluster::remap::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::core::cluster> () (context_a));
	if (valid)
	{
		auto cluster (boost::static_pointer_cast <mu::core::cluster> (context_a.parameters (0)));
		auto cluster_target (boost::make_shared <mu::core::cluster> ());
		(*this) (cluster, cluster_target);
		context_a.push (cluster_target);
	}
	return valid;
}

void mu::script::cluster::remap::operator () (boost::shared_ptr <mu::core::cluster> source, boost::shared_ptr <mu::core::cluster> target)
{
	for (auto i (source->routines.begin ()), j (source->routines.end ()); i != j; ++i)
	{
		auto routine (boost::make_shared <mu::core::routine> ());
		target->routines.push_back (routine);
		(*this) (*i, routine);
	}
}

void mu::script::cluster::remap::operator () (boost::shared_ptr <mu::core::routine> source, boost::shared_ptr <mu::core::routine> target)
{
	auto expression (boost::make_shared <mu::core::expression> ());
	target->body = expression;
	(*this) (source->body, expression);
}

void mu::script::cluster::remap::operator () (boost::shared_ptr <mu::core::expression> source, boost::shared_ptr <mu::core::expression> target)
{
	for (auto i (source->dependencies.begin ()), j (source->dependencies.end ()); i != j; ++i)
	{
		boost::shared_ptr <mu::core::node> value;
		auto existing (mapping.find (*i));
		if (existing != mapping.end ())
		{
			value = existing->second;
		}
		else
		{
			value = *i;
		}
		auto reference (boost::dynamic_pointer_cast <mu::core::reference> (value));
		auto expression (boost::dynamic_pointer_cast <mu::core::expression> (value));
		auto routine (boost::dynamic_pointer_cast <mu::core::routine> (value));
		if (reference.get () != nullptr)
		{
			auto reference_l (boost::make_shared <mu::core::reference> ());
			reference_l->index = reference->index;
			target->dependencies.push_back (reference_l);
			(*this) (reference, reference_l);
		}
		else if (expression.get () != nullptr)
		{
			auto expression_l (boost::make_shared <mu::core::expression> ());
			target->dependencies.push_back (expression_l);
			(*this) (expression, expression_l);
		}
		else if (routine.get () != nullptr)
		{
			target->dependencies.push_back (value);
		}
		else
		{
			target->dependencies.push_back (value);
		}
	}
}

void mu::script::cluster::remap::operator () (boost::shared_ptr <mu::core::reference> source, boost::shared_ptr <mu::core::reference> target)
{
	auto expression (boost::make_shared <mu::core::expression> ());
	target->expression = expression;
	(*this) (source->expression, target->expression);
}