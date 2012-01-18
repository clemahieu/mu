#include "lambda.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p/expression.h>
#include <lambda_p/routine.h>

#include <boost/bind.hpp>

void lambda_p_io::analyzer::extensions::lambda::operator () (lambda_p_io::analyzer::expression & expression_a)
{
	size_t lambda_position (expression_a.position + 1);
	expression_a.position = lambda_position;
	if (expression_a.expression_m->values.size () > lambda_position)
	{
		auto routine (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (expression_a.expression_m->values [lambda_position]));
		if (routine.get () != nullptr)
		{
			lambda_p_io::analyzer::analyzer analyzer (boost::bind (&lambda_p_io::analyzer::extensions::lambda::add, this, expression_a, _1), expression_a.routine.analyzer.errors, expression_a.routine.analyzer.extensions);
			analyzer (routine);
		}
		else
		{
			(*expression_a.routine.analyzer.errors) (L"Lambda extension requires its argument to be an expression");
		}
	}
	else
	{
		(*expression_a.routine.analyzer.errors) (L"Lambda extension requires one argument");
	}
}

void lambda_p_io::analyzer::extensions::lambda::add (lambda_p_io::analyzer::expression & expression_a, boost::shared_ptr <lambda_p::routine> routine_a)
{
	expression_a.self->dependencies.push_back (routine_a);
}