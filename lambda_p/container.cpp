#include "container.h"

void lambda_p::container::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments)
{
	results.assign (arguments.begin (), arguments.end ());
}