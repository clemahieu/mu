#include <io/parser/begin.h>

#include <io/tokens/token.h>
#include <io/parser/parser.h>
#include <io/parser/error.h>
#include <io/parser/values.h>
#include <io/tokens/left_square.h>
#include <io/tokens/divider.h>
#include <io/tokens/identifier.h>
#include <io/tokens/right_square.h>
#include <io/tokens/parameters.h>
#include <core/errors/error_target.h>
#include <io/ast/end.h>

#include <boost/make_shared.hpp>

mu::io::parser::begin::begin (mu::io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <mu::io::ast::node>)> target_a)
	: parser (parser_a),
	target (target_a)
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
    boost::shared_ptr <mu::io::tokens::visitor> new_state (new mu::io::parser::values (parser, target));
    parser.state.push (new_state);
}

void mu::io::parser::begin::operator () (mu::io::tokens::right_square * token)
{
	unexpected_token (token);
}

void mu::io::parser::begin::operator () (mu::io::tokens::stream_end * token)
{
	target (boost::make_shared <mu::io::ast::end> (parser.context));
	parser.state.pop ();
}

void mu::io::parser::begin::operator () (mu::io::tokens::parameters * token)
{
	unexpected_token (token);
}

void mu::io::parser::begin::unexpected_token (mu::io::tokens::token * token)
{
    std::wstring message (L"At top level, expecting signature or end of stream");
	(*parser.errors) (message, parser.context);
    parser.state.push (boost::shared_ptr <mu::io::tokens::visitor> (new mu::io::parser::error));
}