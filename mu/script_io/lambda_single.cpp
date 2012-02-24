#include "lambda_single.h"

#include <mu/io/analyzer/expression.h>
#include <mu/io/ast/expression.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/analyzer/routine.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/io/ast/end.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <sstream>

void mu::script_io::lambda_single::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a)
{
	size_t lambda_position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > lambda_position)
	{
		expression_a.position = lambda_position;
		auto routine (boost::dynamic_pointer_cast <mu::io::ast::expression> (expression_a.expression_m->values [lambda_position]));
		if (routine.get () != nullptr)
		{
			mu::io::analyzer::analyzer analyzer (boost::bind (&mu::script_io::lambda_single::add, this, errors_a, expression_a, _1), expression_a.routine.analyzer.errors, expression_a.routine.analyzer.extensions);
			analyzer.input (routine);
			analyzer.input (boost::make_shared <mu::io::ast::end> (mu::core::context (expression_a.expression_m->context.last, expression_a.expression_m->context.last)));
		}
		else
		{
			(*errors_a) (L"Lambda_single extension requires its argument to be an expression", mu::core::context (expression_a.expression_m->values [lambda_position - 1]->context.first, expression_a.expression_m->values [lambda_position]->context.last));
		}
	}
	else
	{
		(*errors_a) (L"Lambda_single extension requires one argument", expression_a.expression_m->values [lambda_position - 1]->context);
	}
}

void mu::script_io::lambda_single::add (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::io::analyzer::expression & expression_a, boost::shared_ptr <mu::core::cluster> cluster_a)
{
	if (cluster_a->routines.size () == 1)
	{
		expression_a.self->dependencies.push_back (cluster_a->routines [0]);
	}
	else
	{
		(*errors_a) (L"Lambda does not contain one routine");
	}
}