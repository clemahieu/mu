#include "extension.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/expression.h>
#include <lambda_p_io/ast/cluster.h>

#include <boost/make_shared.hpp>

void lambda_p_script::ast::extension::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a)
{
	size_t position (expression_a.position + 1);
	if (position < expression_a.expression_m->values.size ())
	{
		expression_a.position = position;
		auto result (core (errors_a, expression_a.expression_m->values [position]));
		expression_a.self->dependencies.push_back (result);
	}
	else
	{
		(*errors_a) (L"AST extension requires at least one argument");
	}
}

boost::shared_ptr <lambda_p_io::ast::cluster> lambda_p_script::ast::extension::core (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p_io::ast::node> node_a)
{
	auto result (boost::make_shared <lambda_p_io::ast::cluster> ());
	auto value (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (node_a));
	if (value.get () != nullptr)
	{
		if (value->full_name->string.empty () && value->individual_names.empty ())
		{
			bool good (true);
			for (auto i (value->values.begin ()), j (value->values.end ()); i != j && good; ++i)
			{
				auto expression (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (*i));
				if (expression.get () != nullptr)
				{
					result->expressions.push_back (expression);
				}
				else
				{
					good = false;
					(*errors_a) (L"AST argument must only contain expressions");
				}
			}
		}
		else
		{
			(*errors_a) (L"AST extension requires top level to not be named");
		}
	}
	else
	{
		(*errors_a) (L"AST extension requires argument to be an expression");
	}
	return result;
}