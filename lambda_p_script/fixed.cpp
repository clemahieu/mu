#include "fixed.h"

void lambda_p_script::fixed::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (check_count (errors_a, parameters, count ()))
	{
		(*this) (errors_a, parameters, results);
	}
}