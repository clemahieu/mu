#include "add.h"

#include <lambda_p_script/operations/package/package.h>
#include <lambda_p_script/nodes/data.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

void lambda_p_script::operations::package::add::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto expected (check_count (errors_a, parameters, 3));
	if (expected)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_script::operations::package::package> (parameters [0]));
		auto two (boost::dynamic_pointer_cast <lambda_p_script::nodes::data> (parameters [1]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				auto existing (one->items.find (two->string));
				if (existing != one->items.end ())
				{
					one->items.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::node>>::value_type (two->string, parameters [2]));
				}
				else
				{
					std::wstringstream message;
					message << L"Package already has an item named: ";
					message << two->string;
					(*errors_a) (message.str ());
				}
			}
			else
			{
				invalid_type (errors_a, 1);
			}
		}
		else
		{
			invalid_type (errors_a, 0);
		}
	}
}

std::wstring lambda_p_script::operations::package::add::name ()
{
	return std::wstring (L"lambda_p_script::operations::package::add");
}