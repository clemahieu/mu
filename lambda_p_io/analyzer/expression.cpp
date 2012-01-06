#include "expression.h"

#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/analyzer/extension.h>
#include <lambda_p/call.h>
#include <lambda_p/reference.h>
#include <lambda_p_io/analyzer/resolver.h>
#include <lambda_p_io/analyzer/unresolved.h>

lambda_p_io::analyzer::expression::expression (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a)
	: routine (routine_a),
	expression_m (expression_a),
	result (new lambda_p::call),
	unresolved (new lambda_p_io::analyzer::unresolved (expression_a, result)),
	position (0)
{
	for (auto j (expression_a->values.size ()); position != j; ++position)
	{
		(*expression_a->values [position]) (this);
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
			routine.unresolved.insert (std::multimap <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::resolver>>::value_type (identifier_a->string, boost::shared_ptr <lambda_p_io::analyzer::resolver> (new lambda_p_io::analyzer::resolver (unresolved, result))));
			result->dependencies.push_back (boost::shared_ptr <lambda_p::expression> ());
		}
	}
	else
	{
		(*keyword->second) (*this);
	}
}