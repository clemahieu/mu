#include "call.h"

#include <lambda_p/core/node.h>
#include <lambda_p/errors/string_error.h>

lambda_p::core::call::call (boost::shared_ptr <lambda_p::core::target> target_a, boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a)
	: target (target_a),
	errors (errors_a)
{
}

void lambda_p::core::call::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & arguments)
{
	if (!arguments.empty ())
	{
		auto node (boost::dynamic_pointer_cast <lambda_p::core::node> (arguments [0]));
		if (node.get () != nullptr)
		{
			(*node) (arguments, target);
		}
		else
		{
			errors (boost::shared_ptr <lambda_p::errors::error> (new lambda_p::errors::string_error (L"Target of expression is not a node")));
		}
	}
	else
	{
		errors (boost::shared_ptr <lambda_p::errors::error> (new lambda_p::errors::string_error (L"Expression has no call target")));
	}
}