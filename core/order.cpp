#include "order.h"

#include <core/expression.h>
#include <core/reference.h>

mu::core::order::order (boost::shared_ptr <mu::core::expression> call_a)
{
	(*this) (call_a);
}

void mu::core::order::operator () (boost::shared_ptr <mu::core::expression> expression_a)
{
	auto existing (already.find (expression_a));
	if (existing == already.end ())
	{	
		already.insert (expression_a);
		for (auto i (expression_a->dependencies.begin ()), j (expression_a->dependencies.end ()); i != j; ++i)
		{
			current = *i;
			(*(*i)) (this);
		}
		expressions.push_back (expression_a);
	}
}

void mu::core::order::operator() (mu::core::parameters * parameters_a)
{

}

void mu::core::order::operator () (mu::core::expression * set_a)
{
	auto call_l (boost::static_pointer_cast <mu::core::expression> (current));
	(*this) (call_l);
}

void mu::core::order::operator () (mu::core::reference * reference_a)
{
	auto reference_l (boost::static_pointer_cast <mu::core::reference> (current));
	(*this) (reference_l->expression);
}

void mu::core::order::operator () (mu::core::node * node_a)
{

}

void mu::core::order::operator() (mu::core::routine * routine_a)
{

}