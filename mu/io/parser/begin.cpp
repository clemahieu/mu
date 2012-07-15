#include <mu/io/parser/begin.h>

#include <mu/io/tokens/token.h>
#include <mu/io/parser/parser.h>
#include <mu/io/parser/error.h>
#include <mu/io/parser/values.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/parameters.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/tokens/stream_end.h>

#include <gc_cpp.h>

mu::io::parser::begin::begin (mu::io::parser::parser & parser_a)
	: parser (parser_a)
{
}

void mu::io::parser::begin::operator () (mu::io::tokens::divider * token)
{
	unexpected_token (token);
}

void mu::io::parser::begin::operator () (mu::io::tokens::identifier * token)
{
	unexpected_token (token);
}

void mu::io::parser::begin::operator () (mu::io::tokens::left_square * token)
{
    auto new_state (new (GC) mu::io::parser::values (parser, parser));
    parser.state.push (new_state);
}

void mu::io::parser::begin::operator () (mu::io::tokens::right_square * token)
{
	unexpected_token (token);
}

void mu::io::parser::begin::operator () (mu::io::tokens::stream_end * token)
{
	parser.finish ();
}

void mu::io::parser::begin::operator () (mu::io::tokens::parameters * token)
{
	unexpected_token (token);
}

void mu::io::parser::begin::unexpected_token (mu::io::tokens::token * token)
{
    std::wstring message (L"At top level, expecting signature or end of stream");
	(*parser.errors) (message);
    parser.state.push (new (GC) mu::io::parser::error);
}