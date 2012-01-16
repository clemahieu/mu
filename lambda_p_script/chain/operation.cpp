#include "operation.h"

void lambda_p_script::chain::operation::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::operation> (parameters [0]));
	if (one.get () != nullptr)
	{
		std::vector <boost::shared_ptr <lambda_p::node>> arguments (parameters.begin () + 1, parameters.end ());
		std::vector <boost::shared_ptr <lambda_p::node>> results;
		one->perform (errors_a, arguments, results);
	}
	else
	{
		invalid_type (errors_a, 0);
	}
}

std::wstring lambda_p_script::chain::operation::name ()
{
	return std::wstring (L"lambda_p_script::chain::operation");
}