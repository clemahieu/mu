#include "lambda.h"

#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/ast/expression.h>
#include <core/errors/error_list.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <core/expression.h>
#include <core/routine.h>
#include <lambda_p_io/ast/end.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <sstream>

void lambda_p_script_io::lambda::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a)
{
	size_t lambda_position (expression_a.position + 1);
	if (expression_a.expression_m->values.size () > lambda_position)
	{
		expression_a.position = lambda_position;
		auto set (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (expression_a.expression_m->values [lambda_position]));
		if (set.get () != nullptr)
		{
			bool good (true);
			lambda_p_io::analyzer::analyzer analyzer (boost::bind (&lambda_p_script_io::lambda::add, this, expression_a, _1), expression_a.routine.analyzer.errors, expression_a.routine.analyzer.extensions);
			for (auto i (set->values.begin ()), j (set->values.end ()); i != j; ++i)
			{
				auto routine (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (*i));
				if (routine.get () != nullptr)
				{
					analyzer.input (routine);
				}
				else
				{
					good = false;
					std::wstringstream message;
					message << L"Value is not an expression: ";
					message << (*i)->name ();
					(*errors_a) (message.str ());
				}
			}
			if (good)
			{
				analyzer.input (boost::make_shared <lambda_p_io::ast::end> (mu::core::context (expression_a.expression_m->context.last, expression_a.expression_m->context.last)));
			}
		}
		else
		{
			(*errors_a) (L"Lambda extension requires its argument to be an expression", mu::core::context (expression_a.expression_m->values [lambda_position - 1]->context.first, expression_a.expression_m->values [lambda_position]->context.last));
		}
	}
	else
	{
		(*errors_a) (L"Lambda extension requires one argument", expression_a.expression_m->values [lambda_position - 1]->context);
	}
}

void lambda_p_script_io::lambda::add (lambda_p_io::analyzer::expression & expression_a, boost::shared_ptr <mu::core::cluster> cluster_a)
{
	expression_a.self->dependencies.push_back (cluster_a);
}