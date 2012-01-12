#include "order.h"

#include <lambda_p/call.h>

lambda_p_script_io::order::order (boost::shared_ptr <lambda_p::call> call_a)
{
	expressions.push_front (call_a);
	auto location (expressions.begin ());
	already.insert (std::map <boost::shared_ptr <lambda_p::call>, std::list <boost::shared_ptr <lambda_p::call>>::iterator>::value_type (call_a, location));
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
		auto location (expressions.begin ());
		already.insert (std::map <boost::shared_ptr <lambda_p::call>, std::list <boost::shared_ptr <lambda_p::call>>::iterator>::value_type (call_l, location));
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