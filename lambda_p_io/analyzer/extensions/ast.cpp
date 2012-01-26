#include "ast.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/expression.h>

void lambda_p_io::analyzer::extensions::ast::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a)
{
	size_t position (expression_a.position + 1);
	if (position < expression_a.expression_m->values.size ())
	{
		expression_a.position = position;
		auto value (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (expression_a.expression_m->values [position]));
		if (value.get () != nullptr)
		{
			expression_a.self->dependencies.push_back (value);
		}
		else
		{
			(*errors_a) (L"AST extension requires argument to be an expression");
		}
	}
	else
	{
		(*errors_a) (L"AST extension requires at least one argument");
	}
}