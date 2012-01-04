#include "collapse.h"

#include <lambda_p/explode.h>
			
lambda_p::collapse::collapse (boost::shared_ptr <lambda_p::target> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

void lambda_p::collapse::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments)
{
	auto explode (boost::shared_ptr <lambda_p::explode> (new lambda_p::explode (arguments, errors)));
	std::vector <boost::shared_ptr <lambda_p::node>> arguments_l;
	arguments_l.push_back (explode);
	(*target) (arguments_l);
}