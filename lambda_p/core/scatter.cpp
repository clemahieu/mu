#include "scatter.h"

#include <lambda_p/errors/string_error.h>

#include <sstream>

lambda_p::core::scatter::scatter (boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a)
	: required (~0),
	errors (errors_a)
{
}

void lambda_p::core::scatter::operator () (std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments)
{
	if (required != ~0)
	{
		if (arguments.size () != required)
		{
			std::wstringstream message;
			message << L"Actual number of arguments: ";
			message << arguments.size ();
			message << L" doesn't match number of formal arguments: ";
			message << required;
			errors (boost::shared_ptr <lambda_p::errors::error> (new lambda_p::errors::string_error (message.str ())));
		}
		else
		{
			perform (arguments);
		}
		assert (targets.size () <= required);
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
	if (targets.size () <= index)
	{
		targets.resize (index + 1);
	}
	return targets [index];
}

void lambda_p::core::scatter::set_required (size_t required_a)
{
	required = required_a;
}
