#include "builder.h"

#include <boost/bind.hpp>
#include <lambda_p_io/ast/expression.h>

lambda_p_io::builder::builder ()
	: errors (new lambda_p::errors::error_list),
	analyzer (boost::bind (&lambda_p_io::builder::operator (), this, _1), errors),
	parser (boost::bind (&lambda_p_io::analyzer::analyzer::operator (), &analyzer, _1)),
	lexer (boost::bind (&lambda_p_io::parser::parser::operator (), &parser, _1))
{
}

void lambda_p_io::builder::operator () (boost::shared_ptr <lambda_p::routine> routine_a)
{
	routines.push_back (routine_a);
}