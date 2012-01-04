#include "pipe.h"

#include <lambda_p/core/target.h>

void lambda_p::core::pipe::operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & arguments)
{
	(*next) (arguments);
}