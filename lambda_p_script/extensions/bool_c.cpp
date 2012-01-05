#include "bool_c.h"

#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_kernel/nodes/bool_c.h>

#include <sstream>
#include <cctype>

lambda_p_kernel::extensions::bool_c::bool_c ()
{
	boost::shared_ptr <lambda_p_kernel::nodes::bool_c> t (new lambda_p_kernel::nodes::bool_c (true));
	boost::shared_ptr <lambda_p_kernel::nodes::bool_c> f (new lambda_p_kernel::nodes::bool_c (false));
	map [std::wstring (L"true")] = t;
	map [std::wstring (L"1")] = t;
	map [std::wstring (L"t")] = t;
	map [std::wstring (L"on")] = t;
	map [std::wstring (L"yes")] = t;
	map [std::wstring (L"high")] = t;
	map [std::wstring (L"false")] = f;
	map [std::wstring (L"0")] = f;
	map [std::wstring (L"f")] = f;
	map [std::wstring (L"off")] = f;
	map [std::wstring (L"no")] = f;
	map [std::wstring (L"low")] = f;
}

std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::node>>> lambda_p_kernel::extensions::bool_c::operator () (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> & values_a, size_t position_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
{	
	auto data_position (position_a + 1);
	std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::node>>> result;
	if (data_position < values_a.size ())
	{
		auto data_node (values_a [data_position]);
		auto data_identifier (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (data_node));
		if (data_identifier.get () != nullptr)
		{			
			std::wstring string (data_identifier->string);
			std::transform (string.begin (), string.end (), string.begin (), std::tolower);
			auto value (map.find (string));
			if (value != map.end ())
			{
				result.second.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p_kernel::nodes::bool_c (value->second)));
			}
			else
			{
				std::wstringstream message;
				message << L"Cannot convert: ";
				message << data_identifier->string;
				message << L" to a boolean value";
				(*errors_a) (message.str ());
			}
		}
		else
		{
			(*errors_a) (L"Boolean extension requires its argument to be an identifier");
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Boolean extensions at position: ";
		message << position_a;
		message << L" requires one argument";
		(*errors_a) (message.str ());
	}
	result.first = 1;
	return result;
}