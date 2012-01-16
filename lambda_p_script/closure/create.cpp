#include "create.h"

#include <lambda_p_script/closure/operation.h>
#include <lambda_p_script/integer/node.h>

void lambda_p_script::closure::create::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto operation (boost::dynamic_pointer_cast <lambda_p_script::operation> (parameters [0]));
	auto count (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (parameters [1]));
	if (operation.get () != nullptr)
	{
		if (count.get () != nullptr)
		{
			results.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::closure::operation (count->value, operation)));
		}
		else
		{
			invalid_type (errors_a, 1);
		}
	}
	else
	{
		invalid_type (errors_a, 0);
	}
}

size_t lambda_p_script::closure::create::count ()
{
	return 2;
}

std::wstring lambda_p_script::closure::create::name ()
{
	return std::wstring (L"lambda_p_script::closure::create");
}