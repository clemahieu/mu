#include <mu/script/integer_extension.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/integer_node.h>
#include <mu/io/tokens_identifier.h>
#include <mu/io/analyzer_analyzer.h>
#include <mu/io/tokens_value.h>

#include <errno.h>
#include <assert.h>

#include <gc_cpp.h>

mu::script::integer::extension::extension (mu::io::keywording::keywording & keywording_a):
keywording (keywording_a)
{
}

void mu::script::integer::extension::operator () (mu::io::tokens::token * token_a)
{
    assert (dynamic_cast <mu::io::tokens::identifier *> (token_a) != nullptr);
    auto data (static_cast <mu::io::tokens::identifier *> (token_a));
    auto & string (data->string);
    auto result (core (keywording.errors, string));
    if (result != nullptr)
    {
        keywording.state.pop ();
        keywording (new (GC) mu::io::tokens::value (token_a->context, result));
    }
}

mu::script::integer::node * mu::script::integer::core (mu::core::errors::error_target & errors_a, mu::string & string)
{
	mu::script::integer::node * result (nullptr);
	int base (0);
	wchar_t base_char (string [string.length () - 1]);
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
            base = 10;
            break;
	}
    switch (base_char)
    {
		case L'h':
		case L'd':
		case L'o':
		case L'b':
            string.erase (string.end () - 1);
			break;
		default:
            break;
    }
	if (base != 0)
	{
        std::wstring string_l (string.begin (), string.end () - 1);
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