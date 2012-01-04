#include "call.h"

#include <lambda_p/expression.h>
#include <lambda_p/errors/error_target.h>

lambda_p::call::call (boost::shared_ptr <lambda_p::target> target_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

void lambda_p::call::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & arguments)
{
	if (!arguments.empty ())
	{
		auto node (boost::dynamic_pointer_cast <lambda_p::expression> (arguments [0]));
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