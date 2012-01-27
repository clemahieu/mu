#include "lambda.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p/expression.h>
#include <lambda_p/routine.h>
#include <lambda_p_io/ast/end.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void lambda_p_io::analyzer::extensions::lambda::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a)
{
	size_t lambda_position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > lambda_position)
	{
		expression_a.position = lambda_position;
		auto routine (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (expression_a.expression_m->values [lambda_position]));
		if (routine.get () != nullptr)
		{
			lambda_p_io::analyzer::analyzer analyzer (boost::bind (&lambda_p_io::analyzer::extensions::lambda::add, this, expression_a, _1), expression_a.routine.analyzer.errors, expression_a.routine.analyzer.extensions);
			analyzer.input (routine);
			analyzer.input (boost::make_shared <lambda_p_io::ast::end> (lambda_p::context (expression_a.expression_m->context.last, expression_a.expression_m->context.last)));
		}
		else
		{
			(*expression_a.routine.analyzer.errors) (L"Lambda extension requires its argument to be an expression", lambda_p::context (expression_a.expression_m->values [lambda_position - 1]->context.first, expression_a.expression_m->values [lambda_position]->context.last));
		}
	}
	else
	{
		(*expression_a.routine.analyzer.errors) (L"Lambda extension requires one argument", expression_a.expression_m->values [lambda_position - 1]->context);
	}
}

void lambda_p_io::analyzer::extensions::lambda::add (lambda_p_io::analyzer::expression & expression_a, boost::shared_ptr <lambda_p::cluster> cluster_a)
{
	assert (cluster_a->routines.size () == 1);
	expression_a.self->dependencies.push_back (cluster_a->routines.begin ()->second);
}