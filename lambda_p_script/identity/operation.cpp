#include "operation.h"

void lambda_p_script::identity::operation::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	results.insert (results.end (), parameters.begin (), parameters.end ());
}

std::wstring lambda_p_script::identity::operation::name ()
{
	return std::wstring (L"lambda_p_script::identity::operation");
}