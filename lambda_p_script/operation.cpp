#include "operation.h"

#include <lambda_p/errors/error_target.h>

#include <sstream>

bool lambda_p_script::operation::check_count (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, size_t expected)
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
		parameters.size ();
		(*errors_a) (message.str ());
	}
	return result;
}

void lambda_p_script::operation::invalid_type (boost::shared_ptr <lambda_p::errors::error_target> errors_a, size_t position)
{
	std::wstringstream message;
	message << L"In operation: ";
	message << name ();
	message << L"Invalid node type at position: ";
	message << position;
	(*errors_a) (message.str ());
}