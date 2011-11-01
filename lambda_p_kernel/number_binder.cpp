#include "number_binder.h"

#include <lambda_p/binder/data.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_kernel/number.h>
#include <lambda_p/errors/error_list.h>

#include <sstream>

void lambda_p_kernel::number_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	check_count (1, 1, statement, problems);
	if (problems.errors.empty ())
	{
		auto data (boost::dynamic_pointer_cast <lambda_p::binder::data> (nodes [statement->association->references [0]]));
		if (data.get () != nullptr)
		{
			std::wstring string (data->string ());
			boost::shared_ptr <lambda_p_kernel::number> target;
			core (string, target, problems);
			if (target.get () != nullptr)
			{
				nodes [statement->association->declarations [0]] = target;
			}
		}
		else
		{
			unexpected_binder_type_error (0, L"data", problems);
		}
	}
}

std::wstring lambda_p_kernel::number_binder::binder_name ()
{
	return std::wstring (L"number");
}

void lambda_p_kernel::number_binder::core (std::wstring & string, boost::shared_ptr <lambda_p_kernel::number> & target, lambda_p::errors::error_list & problems)
{
	int base;
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
		add_error (message.str (), problems);
		break;
	}
	if (problems.errors.empty ())
	{						
		wchar_t * next;
		wchar_t const * string_l (string.c_str ());
		errno = 0;
		unsigned long number = std::wcstol (string_l, &next, base);
		if (errno == ERANGE)
		{
			std::wstringstream message;
			message << L"Overflow while parsing: ";
			message << string;
			add_error (message.str (), problems);
		}
		else
		{
			target = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (number));
		}
	}
}