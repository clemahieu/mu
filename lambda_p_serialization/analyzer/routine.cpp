#include "routine.h"

#include <lambda_p_serialization/ast/expression.h>
#include <lambda_p_serialization/analyzer/analyzer.h>
#include <lambda_p_serialization/analyzer/expression.h>
#include <lambda_p/core/pipe.h>

lambda_p_serialization::analyzer::routine::routine (lambda_p_serialization::analyzer::analyzer & analyzer_a, lambda_p_serialization::ast::expression * expression_a)
	: analyzer (analyzer_a)
{
	if (expression_a->individual_names.empty () && expression_a->full_name.empty ())
	{
		lambda_p_serialization::analyzer::expression expression (*this, expression_a, pipe);
	}
	else
	{
		analyzer_a.errors (std::wstring (L"Top level routine cannot have individual or a full name"));
	}
}