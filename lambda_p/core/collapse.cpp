#include "collapse.h"

#include <lambda_p/core/explode.h>
			
lambda_p::core::collapse::collapse (boost::shared_ptr <lambda_p::core::target> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

void lambda_p::core::collapse::operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & arguments)
{
	auto explode (boost::shared_ptr <lambda_p::core::explode> (new lambda_p::core::explode (arguments, errors)));
	std::vector <boost::shared_ptr <lambda_p::core::node>> arguments_l;
	arguments_l.push_back (explode);
	(*target) (arguments_l);
}