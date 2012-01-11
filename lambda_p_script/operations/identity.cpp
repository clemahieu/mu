#include "identity.h"

void lambda_p_script::operations::identity::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto begin (parameters.begin ());
	assert (begin != parameters.end ());
	++begin;
	results.assign (begin, parameters.end ());
}

std::wstring lambda_p_script::operations::identity::name ()
{
	return std::wstring (L"lambda_p_script::operations::identity");
}