#include <mu/io/parser/values.h>

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
#include <mu/io/ast/cluster.h>

#include <boost/bind.hpp>

#include <gc_cpp.h>

mu::io::parser::values::values (mu::io::parser::parser & parser_a, mu::io::parser::target & target_a)
	: target (target_a),
	parser (parser_a),
	first (parser_a.context)
{
}

void mu::io::parser::values::operator () (mu::io::tokens::divider * token)
{
	parser.state.pop ();
	parser.state.push (new (GC) mu::io::parser::single (parser, target, values_m, first));
}

void mu::io::parser::values::operator () (mu::io::tokens::identifier * token)
{
	values_m.push_back (new (GC) mu::io::ast::identifier (parser.context, token->string));
}

void mu::io::parser::values::operator () (mu::io::tokens::left_square * token)
{
	parser.state.push (new (GC) mu::io::parser::values (parser, *this));
}

void mu::io::parser::values::operator () (mu::io::tokens::right_square * token)
{
	parser.state.pop ();
    auto expression (new (GC) mu::io::ast::expression (mu::io::debugging::context (first.first, parser.context.last), values_m));
	target (expression);
}

void mu::io::parser::values::operator () (mu::io::tokens::stream_end * token)
{
	(*parser.errors) (U"Unexpected end of stream while parsing expression");
	parser.state.push (new (GC) mu::io::parser::error);
}

void mu::io::parser::values::operator () (mu::io::tokens::parameters * token)
{
	values_m.push_back (new (GC) mu::io::ast::parameters (parser.context));
}

void mu::io::parser::values::operator () (mu::io::ast::expression * expression_a)
{
	values_m.push_back (expression_a);
}