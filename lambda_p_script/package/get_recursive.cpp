#include "get_recursive.h"

#include <sstream>

void lambda_p_script::package::get_recursive::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 0)
	{

	}
	else
	{
		std::wstringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" requires at least one argument";
	}
}

std::wstring lambda_p_script::package::get_recursive::name ()
{
	return std::wstring (L"lambda_p_script::package::get_recursive");
}