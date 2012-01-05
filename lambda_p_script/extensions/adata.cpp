#include "adata.h"

#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_kernel/nodes/adata.h>

#include <sstream>

std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::node>>> lambda_p_kernel::extensions::adata::operator () (std::vector <boost::shared_ptr <lambda_p_io::ast::node>> & values_a, size_t position_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
{
	auto data_position (position_a + 1);
	std::pair <size_t, std::vector <boost::shared_ptr <lambda_p::core::node>>> result;
	if (data_position < values_a.size ())
	{
		auto data_node (values_a [data_position]);
		auto data_identifier (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (data_node));
		if (data_identifier.get () != nullptr)
		{
			std::string adata;
			bool valid (true);
			for (auto i (data_identifier->string.begin ()); i != data_identifier->string.end (); ++i)
			{
				wchar_t val (*i);
				if (val <= CHAR_MAX)
				{
					adata.push_back ((char)val);
				}
				else
				{
					std::wstringstream message;
					message << L"Unable to use as ASCII character: ";
					message << val;
					(*errors_a) (message.str ());
					valid = false;
					i = data_identifier->string.end ();
				}
			}
			if (valid)
			{			
				result.second.push_back (boost::shared_ptr <lambda_p::core::node> (new lambda_p_kernel::nodes::adata (adata)));
			}
		}
		else
		{
			(*errors_a) (L"AData extension requires its argument to be an identifier");
		}
	}
	else
	{
		std::wstringstream message;
		message << L"AData extensions at position: ";
		message << position_a;
		message << L" requires one argument";
		(*errors_a) (message.str ());
	}
	result.first = 1;
	return result;
}