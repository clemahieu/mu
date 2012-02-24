#include "values.h"

#include <mu/io/parser/parser.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/parser/single.h>
#include <mu/io/tokens/right_square.h>
#include <mu/io/tokens/identifier.h>
#include <mu/io/tokens/divider.h>
#include <mu/io/ast/expression.h>
#include <mu/io/parser/error.h>
#include <mu/io/tokens/parameters.h>
#include <mu/io/ast/parameters.h>
#include <mu/core/errors/error_target.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

mu::io::parser::values::values (mu::io::parser::parser & parser_a, boost::function <void (boost::shared_ptr <mu::io::ast::node>)> target_a)
	: parser (parser_a),
	target (target_a),
	first (parser_a.context)
{
}

void mu::io::parser::values::operator () (mu::io::tokens::divider * token)
{
	parser.state.pop ();
	parser.state.push (boost::make_shared <mu::io::parser::single> (parser, target, values_m, first));
}

void mu::io::parser::values::operator () (mu::io::tokens::identifier * token)
{
	values_m.push_back (boost::make_shared <mu::io::ast::identifier> (parser.context, token->string));
}

void mu::io::parser::values::operator () (mu::io::tokens::left_square * token)
{
	parser.state.push (boost::make_shared <mu::io::parser::values> (parser, boost::bind (&mu::io::parser::values::subexpression, this, _1)));
}

void mu::io::parser::values::operator () (mu::io::tokens::right_square * token)
{
	parser.state.pop ();
	target (boost::make_shared <mu::io::ast::expression> (mu::core::context (first.first, parser.context.last), values_m));
}

void mu::io::parser::values::operator () (mu::io::tokens::stream_end * token)
{
	(*parser.errors) (L"Unexpected end of stream while parsing expression", mu::core::context (first.first, parser.context.last));
	parser.state.push (boost::make_shared <mu::io::parser::error> ());
}

void mu::io::parser::values::operator () (mu::io::tokens::parameters * token)
{
	values_m.push_back (boost::make_shared <mu::io::ast::parameters> (parser.context));
}

void mu::io::parser::values::subexpression (boost::shared_ptr <mu::io::ast::node> node_a)
{
	values_m.push_back (node_a);
}