#include <mu/script/integer/extension.h>

#include <mu/io/analyzer/expression.h>
#include <mu/io/analyzer/routine.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/ast/identifier.h>
#include <mu/core/expression.h>
#include <mu/script/integer/node.h>

#include <sstream>

#include <errno.h>

#include <gc_cpp.h>

void mu::script::integer::extension::operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a)
{
	auto data_position (expression_a.position + 1);
	expression_a.position = data_position;
	if (expression_a.expression_m->values.size () > data_position)
	{
		auto data (dynamic_cast <mu::io::ast::identifier *> (expression_a.expression_m->values [data_position]));
		if (data != nullptr)
		{
			auto string (data->string);
			auto result (core (errors_a, string));
			if (result != nullptr)
			{
				expression_a.self->dependencies.push_back (result);
			}
		}
		else
		{
			(*errors_a) (L"Number extension requires its argument to be an identifier");
		}
	}
	else
	{
		(*errors_a) (L"Number extension requires one argument");
	}
}

mu::script::integer::node * mu::script::integer::core (mu::core::errors::error_target * errors_a, std::wstring & string)
{
	mu::script::integer::node * result (nullptr);
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
		wchar_t const * string_l (string.c_str () + 1);
		result = core (errors_a, string_l, base);
	}
	return result;
}

mu::script::integer::node * mu::script::integer::core_d (mu::core::errors::error_target * errors_a, wchar_t const * string_a)
{
	auto result (core (errors_a, string_a, 10));
	return result;
}

mu::script::integer::node * mu::script::integer::core (mu::core::errors::error_target * errors_a, wchar_t const * string_a, size_t base_a)
{
	mu::script::integer::node * result (nullptr);
	wchar_t * next;
	errno = 0;
	unsigned long number = std::wcstoul (string_a, &next, base_a);
	if (errno == ERANGE)
	{
		std::wstringstream message;
		message << L"Overflow while parsing: ";
		message << string_a;
		message << L" in base: ";
		message << base_a;
		(*errors_a) (message.str ());
	}
	else
	{
		result = new (GC) mu::script::integer::node (number);
	}
	return result;
}