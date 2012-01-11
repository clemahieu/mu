#include "create.h"

#include <lambda_p_script/closure/operation.h>

void lambda_p_script::closure::create::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto fixed (boost::dynamic_pointer_cast <lambda_p_script::fixed> (parameters [0]));
	if (fixed.get () != nullptr)
	{
		results.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::operation (fixed->count (), fixed)));
	}
	else
	{
		invalid_type (errors_a, 0);
	}
}

size_t lambda_p_script::closure::create::count ()
{
	return 1;
}

std::wstring lambda_p_script::closure::create::name ()
{
	return std::wstring (L"lambda_p_script::closure::create");
}