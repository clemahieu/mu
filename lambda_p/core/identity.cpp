#include "identity.h"

#include <lambda_p/core/target.h>

void lambda_p::core::identity::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & parameters, boost::shared_ptr <lambda_p::core::target> target_a)
{
	auto i (parameters.begin ());
	auto j (parameters.end ());
	assert (i != j);
	++i;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments (i, j);
	(*target_a) (arguments);
}