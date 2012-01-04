#include "number.h"

#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/errors/error_target.h>

#include <sstream>

std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::node>>> lambda_p_kernel::extensions::number::operator () (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> & values_a, size_t position_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
{	
	auto data_position (position_a + 1);
	std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::node>>> result;
	if (data_position < values_a.size ())
	{
		auto data_node (values_a [data_position]);
		auto data_identifier (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (data_node));
		if (data_identifier.get () != nullptr)
		{
			auto string (data_identifier->string);
			int base (0);
			wchar_t base_char (string [0]);
			switch (base_char)
			{
			case L'h':
				base = 16;
				break;
			case L'd':
				base = 10;
				break;
			case L'o':
				base = 8;
				break;
			case L'b':
				base = 2;
				break;
			default:
				std::wstringstream message;
				message << L"Unexpected base prefix: ";
				message << base_char;
				message << L" when trying to parse number: ";
				message << string;
				(*errors_a) (message.str ());
				break;
			}
			if (base != 0)
			{						
				wchar_t * next;
				wchar_t const * string_l (string.c_str () + 1);
				errno = 0;
				unsigned long number = std::wcstol (string_l, &next, base);
				if (errno == ERANGE)
				{
					std::wstringstream message;
					message << L"Overflow while parsing: ";
					message << string;
					(*errors_a) (message.str ());
				}
				else
				{
					result.second.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p_kernel::nodes::number (number)));
				}
			}
		}
		else
		{
			(*errors_a) (L"Number extension requires its argument to be an identifier");
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Number extensions at position: ";
		message << position_a;
		message << L" requires one argument";
		(*errors_a) (message.str ());
	}
	result.first = 1;
	return result;
}