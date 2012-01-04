#include "adapter.h"

#include <lambda_p/expression.h>

void lambda_p::adapter::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments)
{
	(*node) (arguments, target);
}