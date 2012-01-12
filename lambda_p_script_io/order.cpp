#include "order.h"

#include <lambda_p/call.h>

lambda_p_script_io::order::order (boost::shared_ptr <lambda_p::call> call_a)
{
	expressions.push_front (call_a);
	already.insert (call_a);
	(*this) (call_a);
}

void lambda_p_script_io::order::operator () (boost::shared_ptr <lambda_p::call> call_a)
{
	for (auto i (call_a->dependencies.begin ()), j (call_a->dependencies.end ()); i != j; ++i)
	{
		current = *i;
		(*(*i)) (this);
	}
}

void lambda_p_script_io::order::operator () (lambda_p::call * call_a)
{
	auto call_l (boost::static_pointer_cast <lambda_p::call> (current));
	auto existing (already.find (call_l));
	if (existing == already.end ())
	{
		expressions.push_front (call_l);
		already.insert (call_l);
	}
}

void lambda_p_script_io::order::operator () (lambda_p::parameters * parameters_a)
{

}

void lambda_p_script_io::order::operator () (lambda_p::reference * reference_a)
{

}

void lambda_p_script_io::order::operator () (lambda_p::node * node_a)
{

}