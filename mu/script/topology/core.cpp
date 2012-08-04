#include <mu/script/topology/core.h>

#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/script/topology/node.h>

#include <gc_cpp.h>

mu::script::topology::core::core (mu::core::expression * call_a)
	: topology (new (GC) mu::script::topology::node),
	acyclic (true)
{
    perform (call_a);
}

void mu::script::topology::core::perform (mu::core::expression * expression_a)
{
	if (path.find (expression_a) != path.end ())
	{
		acyclic = false;
	}
	path.insert (expression_a);
	auto existing (already.find (expression_a));
	if (existing == already.end ())
	{	
		already.insert (expression_a);
		for (auto i (expression_a->dependencies.begin ()), j (expression_a->dependencies.end ()); i != j; ++i)
		{
			current = *i;
			(*(*i)) (this);
		}
		topology->expressions.push_back (expression_a);
	}
	path.erase (expression_a);    
}

void mu::script::topology::core::operator() (mu::core::cluster * cluster_a)
{
}

void mu::script::topology::core::operator() (mu::core::parameters * parameters_a)
{
}

void mu::script::topology::core::operator () (mu::core::expression * set_a)
{
	auto call_l (static_cast <mu::core::expression *> (current));
	perform (call_l);
}

void mu::script::topology::core::operator () (mu::core::reference * reference_a)
{
	auto reference_l (static_cast <mu::core::reference *> (current));
	perform (reference_l->expression);
}

void mu::script::topology::core::operator () (mu::core::node * node_a)
{
}

void mu::script::topology::core::operator() (mu::core::routine * routine_a)
{
}