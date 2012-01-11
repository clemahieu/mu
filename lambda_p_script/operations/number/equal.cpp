#include "equal.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/nodes/number.h>
#include <lambda_p_script/nodes/bool_c.h>

void lambda_p_script::operations::number::equal::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::nodes::number> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::nodes::number> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			results.push_back (boost::shared_ptr <lambda_p_script::nodes::bool_c> (new lambda_p_script::nodes::bool_c (one->value == two->value)));
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

std::wstring lambda_p_script::operations::number::equal::name ()
{
	return std::wstring (L"lambda_p_script::operations::number::equal");
}

size_t lambda_p_script::operations::number::equal::count ()
{
	return 2;
}