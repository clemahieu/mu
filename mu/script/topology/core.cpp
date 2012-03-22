#include <mu/script/topology/core.h>

#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/script/topology/node.h>

mu::script::topology::core::core (boost::shared_ptr <mu::core::expression> call_a)
	: topology (new mu::script::topology::node),
	acyclic (true)
{
	(*this) (call_a);
}

void mu::script::topology::core::operator() (mu::core::cluster * cluster_a)
{
}

void mu::script::topology::core::operator () (boost::shared_ptr <mu::core::expression> expression_a)
{
	auto existing (already.find (expression_a));
	if (existing == already.end ())
	{	
		if (path.find (expression_a) != path.end ())
		{
			acyclic = false;
		}
		already.insert (expression_a);
		path.insert (expression_a);
		for (auto i (expression_a->dependencies.begin ()), j (expression_a->dependencies.end ()); i != j; ++i)
		{
			current = *i;
			(*(*i)) (this);
		}
		path.erase (expression_a);
		topology->expressions.push_back (expression_a);
	}
}

void mu::script::topology::core::operator() (mu::core::parameters * parameters_a)
{
}

void mu::script::topology::core::operator () (mu::core::expression * set_a)
{
	auto call_l (boost::static_pointer_cast <mu::core::expression> (current));
	(*this) (call_l);
}

void mu::script::topology::core::operator () (mu::core::reference * reference_a)
{
	auto reference_l (boost::static_pointer_cast <mu::core::reference> (current));
	(*this) (reference_l->expression);
}

void mu::script::topology::core::operator () (mu::core::node * node_a)
{
}

void mu::script::topology::core::operator() (mu::core::routine * routine_a)
{
}