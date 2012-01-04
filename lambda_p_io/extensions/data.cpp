#include "data.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p/core/fixed.h>
#include <lambda_p/core/data.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p/core/gather.h>
#include <lambda_p/core/connection.h>
#include <lambda_p/core/tee.h>

#include <sstream>

std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::expression>>> lambda_p_io::extensions::data::operator () (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> & values_a, size_t position_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
{
	auto data_position (position_a + 1);
	std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::expression>>> result;
	if (data_position < values_a.size ())
	{
		auto data_node (values_a [data_position]);
		auto data_identifier (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (data_node));
		if (data_identifier.get () != nullptr)
		{
			result.second.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::data (data_identifier->string)));
		}
		else
		{
			(*errors_a) (L"Data extension requires its argument to be an identifier");
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Data extensions at position: ";
		message << position_a;
		message << L" requires one argument";
		(*errors_a) (message.str ());
	}
	result.first = 1;
	return result;
}