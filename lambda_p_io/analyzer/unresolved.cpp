#include "unresolved.h"

#include <lambda_p/reference.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/call.h>
#include <lambda_p_io/analyzer/routine.h>

lambda_p_io::analyzer::unresolved::unresolved (lambda_p_io::ast::expression * expression_a, boost::shared_ptr <lambda_p::call> result_a)
	: complete (false),
	count (0),
	expression (expression_a),
	result (result_a)
{
}

void lambda_p_io::analyzer::unresolved::operator () (lambda_p_io::analyzer::routine & routine_a)
{
	if (complete && count == 0)
	{
		size_t position (0);
		for (auto i (expression->individual_names.begin ()), j (expression->individual_names.end ()); i != j; ++i, ++position)
		{
			auto reference (boost::shared_ptr <lambda_p::reference> (new lambda_p::reference));
			reference->index = position;
			reference->call = result;
			routine_a (*i, reference);
		}
		if (!expression->full_name.empty ())
		{
			routine_a (expression->full_name, result);
		}
	}
}