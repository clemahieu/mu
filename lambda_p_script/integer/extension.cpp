#include "extension.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/call.h>
#include <lambda_p_script/integer/node.h>

#include <sstream>

void lambda_p_script::integer::extension::operator () (lambda_p_io::analyzer::expression & expression_a)
{
	auto data_position (expression_a.position + 1);
	expression_a.position = data_position;
	if (expression_a.expression_m->values.size () > data_position)
	{
		auto data (boost::dynamic_pointer_cast <lambda_p_io::ast::identifier> (expression_a.expression_m->values [data_position]));
		if (data.get () != nullptr)
		{
			auto string (data->string);
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
					(*expression_a.routine.analyzer.errors) (message.str ());
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
					(*expression_a.routine.analyzer.errors) (message.str ());
				}
				else
				{
					expression_a.self->dependencies.push_back (boost::shared_ptr <lambda_p_script::integer::node> (new lambda_p_script::integer::node (number)));
				}
			}
		}
		else
		{
			(*expression_a.routine.analyzer.errors) (L"Number extension requires its argument to be an identifier");
		}
	}
	else
	{
		(*expression_a.routine.analyzer.errors) (L"Number extension requires one argument");
	}
}