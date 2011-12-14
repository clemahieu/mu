#include "pipe.h"

void lambda_p::core::pipe::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	(*next) (arguments);
}