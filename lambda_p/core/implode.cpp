#include "implode.h"

#include <lambda_p/core/explode.h>
#include <lambda_p/core/target.h>

lambda_p::core::implode::implode (boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: errors (errors_a)
{
}

void lambda_p::core::implode::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & parameters, boost::shared_ptr <lambda_p::core::target> target_a)
{
	assert (parameters.size () > 0);
	assert (parameters [0].get () == this);
	std::vector <boost::shared_ptr <lambda_p::core::expression>> parameters_l (++parameters.begin (), parameters.end ());
	auto explode (boost::shared_ptr <lambda_p::core::explode> (new lambda_p::core::explode (parameters_l, errors)));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	arguments.push_back (explode);
	(*target_a) (arguments);
}