#include "constant.h"

lambda_p_script::runtime::constant::constant (boost::shared_ptr <lambda_p::node> value_a)
	: value (value_a)
{
}

void lambda_p_script::runtime::constant::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::runtime::context & context, std::vector <boost::shared_ptr <lambda_p::node>> & target)
{
	target.push_back (value);
}