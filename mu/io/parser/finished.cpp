#include <mu/io/parser/finished.h>

#include <mu/io/parser/error.h>
#include <mu/io/parser/parser.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/left_square.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/stream_end.h>
#include <mu/io/tokens/value.h>
#include <mu/core/errors/error_target.h>

#include <gc_cpp.h>

mu::io::parser::finished::finished (mu::io::parser::parser & parser_a)
	: parser (parser_a)
{
}

void mu::io::parser::finished::operator () (mu::io::tokens::divider * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::identifier * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::left_square * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::right_square * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::stream_end * token)
{
	add_error (token);
}

void mu::io::parser::finished::operator () (mu::io::tokens::value * token)
{
	add_error (token);
}

void mu::io::parser::finished::add_error (mu::io::tokens::token * token)
{
    mu::string message (U"Token received after parser is finished");
	parser.errors (message);
	parser.state.push (new (GC) mu::io::parser::error);
}