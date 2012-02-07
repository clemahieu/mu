#include "create.h"

#include <lambda_p_script/values/operation.h>

#include <boost/make_shared.hpp>

void lambda_p_script::values::create::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	std::vector <boost::shared_ptr <lambda_p::node>> values;
	for (auto i (parameters.begin ()), j (parameters.end ()); i != j; ++i)
	{
		values.push_back (*i);
	}
	results.push_back (boost::make_shared <lambda_p_script::values::operation> (values));
}