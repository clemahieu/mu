#include "implode.h"

#include <lambda_p/explode.h>
#include <lambda_p/target.h>

lambda_p::implode::implode (boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: errors (errors_a)
{
}

void lambda_p::implode::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & parameters, boost::shared_ptr <lambda_p::target> target_a)
{
	assert (parameters.size () > 0);
	assert (parameters [0].get () == this);
	std::vector <boost::shared_ptr <lambda_p::node>> parameters_l (++parameters.begin (), parameters.end ());
	auto explode (boost::shared_ptr <lambda_p::explode> (new lambda_p::explode (parameters_l, errors)));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (explode);
	(*target_a) (arguments);
}