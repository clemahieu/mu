#include "container.h"

void lambda_p::container::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & arguments)
{
	results.assign (arguments.begin (), arguments.end ());
}