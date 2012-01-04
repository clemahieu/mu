#include "pipe.h"

#include <lambda_p/target.h>

void lambda_p::pipe::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments)
{
	(*next) (arguments);
}