#include <mu/script/integer_extension.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/integer_node.h>
#include <mu/io/tokens_identifier.h>
#include <mu/io/analyzer_analyzer.h>
#include <mu/io/tokens_value.h>

#include <errno.h>
#include <assert.h>

#include <gc_cpp.h>

mu::script::integer::extension::extension (mu::io::analyzer::analyzer & analyzer_a):
analyzer (analyzer_a)
{
}

void mu::script::integer::extension::operator () (mu::io::tokens::token const & token_a)
{
    assert (dynamic_cast <mu::io::tokens::identifier const *> (&token_a) != nullptr);
    auto data (static_cast <mu::io::tokens::identifier const *> (&token_a));
    auto & string (data->string);
    auto result (core (analyzer.errors, string));
    if (result != nullptr)
    {
        analyzer.state.pop ();
        analyzer (mu::io::tokens::value (token_a.context, result));
    }
}

mu::script::integer::node * mu::script::integer::core (mu::core::errors::error_target & errors_a, mu::string const & string)
{
	mu::script::integer::node * result (nullptr);
	int base (0);
	wchar_t base_char (string [string.length () - 1]);
	switch (base_char)
	{
		case U'h':
			base = 16;
			break;
		case U'd':
			base = 10;
			break;
		case U'o':
			base = 8;
			break;
		case U'b':
			base = 2;
			break;
		default:
            base = 10;
            break;
	}
    std::wstring string_l (string.begin (), string.end ());
    switch (base_char)
    {
        case U'h':
        case U'd':
        case U'o':
        case U'b':
            string_l.erase (string_l.end ());
            break;
        default:
            break;
    }
	assert (base != 0);
	result = core (errors_a, string_l.c_str (), base);
	return result;
}

mu::script::integer::node * mu::script::integer::core_d (mu::core::errors::error_target & errors_a, wchar_t const * string_a)
{
	auto result (core (errors_a, string_a, 10));
	return result;
}

mu::script::integer::node * mu::script::integer::core (mu::core::errors::error_target & errors_a, wchar_t const * string_a, size_t base_a)
{
	mu::script::integer::node * result (nullptr);
	wchar_t * next;
	errno = 0;
	auto number (std::wcstoull (string_a, &next, base_a));
	if (errno == ERANGE)
	{
		mu::stringstream message;
		message << U"Overflow while parsing: ";
        std::wstring string_l (string_a);
		message << mu::string (string_l.begin (), string_l.end ());
		message << U" in base: ";
		message << base_a;
		errors_a (message.str ());
	}
	else
	{
		result = new (GC) mu::script::integer::node (number);
	}
	return result;
}