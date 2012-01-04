#include "expression.h"

#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/analyzer/extension.h>
#include <lambda_p/expression.h>

lambda_p_io::analyzer::expression::expression (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a)
	: routine (routine_a),
	expression_m (expression_a),
	result (new lambda_p::expression),
	complete (true)
{
	for (auto i (expression_a->values.begin ()), j (expression_a->values.end ()); i != j; ++i)
	{
		(*(*i)) (this);
	}
	if (complete)
	{
		for (auto i (expression_a->individual_names.begin ()), j (expression_a->individual_names.end ()); i != j; ++i)
		{
			routine_a (*i, result);
		}
		if (!expression_a->full_name.empty ())
		{
			routine_a (expression_a->full_name, result);
		}
	}
}

void lambda_p_io::analyzer::expression::operator () (lambda_p_io::ast::expression * expression_a)
{
	lambda_p_io::analyzer::expression expression (routine, expression_a);
	result->dependencies.insert (expression.result);
}

void lambda_p_io::analyzer::expression::operator () (lambda_p_io::ast::identifier * identifier_a)
{
	auto keyword (routine.analyzer.extensions.find (identifier_a->string));
	if (keyword == routine.analyzer.extensions.end ())
	{
		auto existing (routine.declarations.find (identifier_a->string));
		if (existing != routine.declarations.end ())
		{
			result->dependencies.insert (existing->second);
		}
		else
		{
			auto mapping (routine.unresolved [identifier_a->string]);
			mapping.insert (expression_m);
			complete = false;
		}
	}
	else
	{
		assert (false);
	}
}