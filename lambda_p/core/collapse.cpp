#include "collapse.h"

#include <lambda_p/core/explode.h>
			
lambda_p::core::collapse::collapse (boost::shared_ptr <lambda_p::core::target> target_a, boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

void lambda_p::core::collapse::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	auto explode (boost::shared_ptr <lambda_p::core::explode> (new lambda_p::core::explode (arguments, errors)));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments_l;
	arguments_l.push_back (explode);
	(*target) (arguments_l);
}