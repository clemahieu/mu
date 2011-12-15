#include "adapter.h"

#include <lambda_p/core/node.h>

void lambda_p::core::adapter::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	(*node) (arguments, target);
}