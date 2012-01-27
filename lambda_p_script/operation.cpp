#include "operation.h"

#include <lambda_p/errors/error_target.h>

#include <sstream>

bool lambda_p_script::operation::check_count (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, size_t expected)
{
	bool result (parameters.size () == expected);
	if (!result)
	{
		std::wstringstream message;
		message << L"In operation: ";
		message << name ();
		message << L" expecting: ";
		message << expected;
		message << L" arguments, have: ";
		message << parameters.size ();
		(*errors_a) (message.str ());
	}
	return result;
}

void lambda_p_script::operation::invalid_type (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::node> node_a, size_t position)
{
	std::wstringstream message;
	message << L"In operation: ";
	message << name ();
	message << L" invalid node type:";
	message << node_a->name ();
	message << L" at position: ";
	message << position;
	(*errors_a) (message.str ());
}