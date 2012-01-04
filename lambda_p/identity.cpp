#include "identity.h"

#include <lambda_p/target.h>

void lambda_p::identity::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & parameters, boost::shared_ptr <lambda_p::target> target_a)
{
	auto i (parameters.begin ());
	auto j (parameters.end ());
	assert (i != j);
	++i;
	std::vector <boost::shared_ptr <lambda_p::node>> arguments (i, j);
	(*target_a) (arguments);
}