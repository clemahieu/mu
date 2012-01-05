#include "expression.h"

#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/analyzer/extension.h>
#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p_io/analyzer/resolver.h>
#include <lambda_p_io/analyzer/unresolved.h>

lambda_p_io::analyzer::expression::expression (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a)
	: routine (routine_a),
	expression_m (expression_a),
	result (new lambda_p::expression),
	unresolved (new lambda_p_io::analyzer::unresolved (expression_a, result))
{
	for (auto i (expression_a->values.begin ()), j (expression_a->values.end ()); i != j; ++i)
	{
		(*(*i)) (this);
	}
	unresolved->complete = true;
	(*unresolved) (routine_a);
}

void lambda_p_io::analyzer::expression::operator () (lambda_p_io::ast::expression * expression_a)
{
	lambda_p_io::analyzer::expression expression (routine, expression_a);
	result->dependencies.push_back (expression.result);
}

void lambda_p_io::analyzer::expression::operator () (lambda_p_io::ast::identifier * identifier_a)
{
	auto keyword (routine.analyzer.extensions.find (identifier_a->string));
	if (keyword == routine.analyzer.extensions.end ())
	{
		auto existing (routine.declarations.find (identifier_a->string));
		if (existing != routine.declarations.end ())
		{
			result->dependencies.push_back (existing->second);
		}
		else
		{
			++unresolved->count;
			auto resolver (boost::shared_ptr <lambda_p_io::analyzer::resolver> (new lambda_p_io::analyzer::resolver (unresolved, result, result->dependencies.size ())));
			routine.unresolved.insert (std::multimap <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::resolver>>::value_type (identifier_a->string, resolver));
			result->dependencies.push_back (boost::shared_ptr <lambda_p::expression> ());
		}
	}
	else
	{
		assert (false);
	}
}