#include "operation.h"

#include <lambda_p_script/data/node.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

void lambda_p_script::package::operation::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto name (boost::dynamic_pointer_cast <lambda_p_script::data::node> (parameters [0]));
	if (name.get () != nullptr)
	{
		auto existing (items.find (name->string));
		if (existing != items.end ())
		{
			results.push_back (existing->second);
		}
		else
		{
			std::wstringstream message;
			message << L"Package does not contain item named: ";
			message << name->string;
			(*errors_a) (message.str ());
		}
	}
	else
	{
		invalid_type (errors_a, 0);
	}
}

std::wstring lambda_p_script::package::operation::name ()
{
	return std::wstring (L"lambda_p_script::package::operation");
}

size_t lambda_p_script::package::operation::count ()
{
	return 1;
}