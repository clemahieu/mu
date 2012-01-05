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

lambda_p_io::analyzer::expression::expression (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a)
	: routine (routine_a),
	expression_m (expression_a),
	result (new lambda_p::expression),
	resolver (new lambda_p_io::analyzer::resolver)
{
	resolver->complete = false;
	for (auto i (expression_a->values.begin ()), j (expression_a->values.end ()); i != j; ++i)
	{
		(*(*i)) (this);
	}
	size_t position (0);
	for (auto i (expression_a->individual_names.begin ()), j (expression_a->individual_names.end ()); i != j; ++i, ++position)
	{
		auto reference (boost::shared_ptr <lambda_p::reference> (new lambda_p::reference));
		reference->index = position;
		reference->expression = result;
		routine_a (*i, reference);
	}
	if (!expression_a->full_name.empty ())
	{
		routine_a (expression_a->full_name, result);
	}
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
			routine.unresolved.insert (std::multimap <std::wstring, std::pair <boost::shared_ptr <lambda_p::expression>, size_t>>::value_type (identifier_a->string, std::pair <boost::shared_ptr <lambda_p::expression>, size_t> (result, result->dependencies.size ())));
			result->dependencies.push_back (boost::shared_ptr <lambda_p::expression> ());
		}
	}
	else
	{
		assert (false);
	}
}