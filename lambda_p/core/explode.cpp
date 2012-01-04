#include "explode.h"

#include <lambda_p/core/target.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

lambda_p::core::explode::explode (std::vector <boost::shared_ptr <lambda_p::core::node>> items_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: items (items_a),
	errors (errors_a)
{
}

void lambda_p::core::explode::operator () (std::vector <boost::shared_ptr <lambda_p::core::node>> & parameters, boost::shared_ptr <lambda_p::core::target> target_a)
{
	assert (parameters.size () > 0);
	if (parameters.size () == 1)
	{
		assert (parameters [0].get () == this);
		(*target_a) (items);
	}
	else
	{
		std::wstringstream message;
		message << L"Explode expects no arguments, have: ";
		message << parameters.size () - 1;
		(*errors) (message.str ());
	}
}