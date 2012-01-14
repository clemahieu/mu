#include "order.h"

#include <lambda_p/set.h>
#include <lambda_p/call.h>

lambda_p_script_io::order::order (boost::shared_ptr <lambda_p::expression> call_a)
{
	(*this) (call_a);
}

void lambda_p_script_io::order::operator () (boost::shared_ptr <lambda_p::expression> expression_a)
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

void lambda_p_script_io::order::operator () (lambda_p::set * set_a)
{
	auto call_l (boost::static_pointer_cast <lambda_p::set> (current));
	(*this) (call_l);
}

void lambda_p_script_io::order::operator () (lambda_p::call * call_a)
{
	auto call_l (boost::static_pointer_cast <lambda_p::call> (current));
	(*this) (call_l);
}

void lambda_p_script_io::order::operator () (lambda_p::reference * reference_a)
{

}

void lambda_p_script_io::order::operator () (lambda_p::node * node_a)
{

}