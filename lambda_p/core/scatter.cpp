#include "scatter.h"

#include <lambda_p/errors/error_target.h>

#include <sstream>

lambda_p::core::scatter::scatter (size_t required_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: required (required_a),
	errors (errors_a),
	targets (required_a)
{
}

void lambda_p::core::scatter::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> & arguments)
{
	if (arguments.size () != required)
	{
		std::wstringstream message;
		message << L"Actual number of arguments: ";
		message << arguments.size ();
		message << L" doesn't match number of formal arguments: ";
		message << required;
		(*errors) (message.str ());
	}
	else
	{
		perform (arguments);
	}
}

void lambda_p::core::scatter::perform (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	auto argument_current (arguments.begin ());
	auto argument_end (arguments.end ());
	for (auto target_current (targets.begin ()), target_end (targets.end ()); target_current != target_end; ++target_current, ++argument_current)
	{
		auto current (*target_current);
		for (auto i (current.begin ()), j (current.end ()); i != j; ++i)
		{
			std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
			arguments.push_back (*argument_current);
			(*(*i)) (arguments);
		}
	}
}
			
std::vector <boost::shared_ptr <lambda_p::core::target>> & lambda_p::core::scatter::operator [] (size_t index)
{
	assert (targets.size () > index);
	return targets [index];
}