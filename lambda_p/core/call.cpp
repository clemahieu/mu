#include "call.h"

#include <lambda_p/core/expression.h>
#include <lambda_p/errors/error_target.h>

lambda_p::core::call::call (boost::shared_ptr <lambda_p::core::target> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

void lambda_p::core::call::operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & arguments)
{
	if (!arguments.empty ())
	{
		auto node (boost::dynamic_pointer_cast <lambda_p::core::expression> (arguments [0]));
		if (node.get () != nullptr)
		{
			(*node) (arguments, target);
		}
		else
		{
			(*errors) (L"Target of expression is not a node");
		}
	}
	else
	{
		(*errors) (L"Expression has no call target");
	}
}