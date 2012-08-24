#include <mu/script/integer/extension.h>

#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/ast/identifier.h>
#include <mu/script/integer/node.h>

#include <sstream>

#include <errno.h>

#include <gc_cpp.h>

mu::script::integer::extension::extension (mu::io::keywording::keywording & keywording_a):
keywording (keywording_a)
{
}

void mu::script::integer::extension::operator () (mu::io::tokens::token * token_a, mu::io::debugging::context context_a)
{
    assert (false);
    /*
    assert (remaining.empty ());
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
			errors_a (U"Number extension requires its argument to be an identifier");
		}
	}
	else
	{
		errors_a (U"Number extension requires one argument");
	}*/
}

mu::script::integer::node * mu::script::integer::core (mu::core::errors::error_target & errors_a, mu::string & string)
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
			mu::stringstream message;
			message << L"Unexpected base prefix: ";
			message << base_char;
			message << L" when trying to parse number: ";
			message << string;
			errors_a (message.str ());
		break;
	}
	if (base != 0)
	{
        std::wstring string_l (string.begin () + 1, string.end ());
		//char32_t const * string_l (string.c_str () + 1);
		result = core (errors_a, string_l, base);
	}
	return result;
}

mu::script::integer::node * mu::script::integer::core_d (mu::core::errors::error_target & errors_a, std::wstring string_a)
{
	auto result (core (errors_a, string_a, 10));
	return result;
}

mu::script::integer::node * mu::script::integer::core (mu::core::errors::error_target & errors_a, std::wstring string_a, size_t base_a)
{
	mu::script::integer::node * result (nullptr);
	wchar_t * next;
	errno = 0;
	unsigned long number = std::wcstoul (string_a.c_str (), &next, base_a);
	if (errno == ERANGE)
	{
		mu::stringstream message;
		message << L"Overflow while parsing: ";
		message << mu::string (string_a.begin (), string_a.end ());
		message << L" in base: ";
		message << base_a;
		errors_a (message.str ());
	}
	else
	{
		result = new (GC) mu::script::integer::node (number);
	}
	return result;
}