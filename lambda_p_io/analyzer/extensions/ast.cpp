#include "ast.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p/expression.h>
#include <lambda_p_io/analyzer/extensions/cluster.h>

#include <boost/make_shared.hpp>

void lambda_p_io::analyzer::extensions::ast::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_io::analyzer::expression & expression_a)
{
	size_t position (expression_a.position + 1);
	if (position < expression_a.expression_m->values.size ())
	{
		expression_a.position = position;
		auto value (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (expression_a.expression_m->values [position]));
		if (value.get () != nullptr)
		{
			if (value->full_name->string.empty () && value->individual_names.empty ())
			{
				auto cluster (boost::make_shared <lambda_p_io::analyzer::extensions::cluster> ());
				bool good (true);
				for (auto i (value->values.begin ()), j (value->values.end ()); i != j && good; ++i)
				{
					auto expression (boost::dynamic_pointer_cast <lambda_p_io::ast::expression> (*i));
					if (expression.get () != nullptr)
					{
						cluster->expressions.push_back (expression);
					}
					else
					{
						good = false;
						(*errors_a) (L"AST argument must only contain expressions");
					}
				}
				if (good)
				{
					expression_a.self->dependencies.push_back (cluster);
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
	}
	else
	{
		(*errors_a) (L"AST extension requires at least one argument");
	}
}