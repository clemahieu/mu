#include "call.h"

#include <lambda_p/core/node.h>

lambda_p::core::call::call (boost::shared_ptr <lambda_p::core::target> target_a)
	: target (target_a)
{
}

void lambda_p::core::call::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	assert (arguments.size () > 0);
	auto node (boost::dynamic_pointer_cast <lambda_p::core::node> (arguments [0]));
	assert (node.get () != nullptr);
	(*node) (arguments, target);
}