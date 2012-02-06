#include "operation.h"

#include <lambda_p/errors/error_target.h>

#include <sstream>

bool lambda_p_llvm::operation::check_size (boost::shared_ptr <lambda_p::errors::error_target> errors_a, size_t expected_a, size_t actual_a)
{
	bool result (expected_a == actual_a);
	if (!result)
	{
		std::wstringstream message;
		message << L"Actual number of arguments: ";
		message << actual_a;
		message << L" does not match expected number of arguments: ";
		message << expected_a;
		(*errors_a) (message.str ());
	}
	return result;
}

void lambda_p_llvm::operation::invalid_type (boost::shared_ptr <lambda_p::errors::error_target> errors_a, size_t position)
{
	std::wstringstream message;
	message << L"Argument at position: ";
	message << position;
	message << L" is not the correct type.";
	(*errors_a) (message.str ());
}