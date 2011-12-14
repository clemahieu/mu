#include "adapter.h"

#include <lambda_p/core/connection.h>

void lambda_p::core::adapter::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	(*connection) (arguments, target);
}