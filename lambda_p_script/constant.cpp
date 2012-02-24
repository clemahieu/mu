#include "constant.h"

lambda_p_script::constant::constant (boost::shared_ptr <mu::core::node> value_a)
	: value (value_a)
{
}

void lambda_p_script::constant::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, lambda_p_script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target)
{
	target.push_back (value);
}