#include "expression.h"

#include <lambda_p_serialization/ast/expression.h>
#include <lambda_p_serialization/ast/identifier.h>
#include <lambda_p_serialization/analyzer/routine.h>
#include <lambda_p/core/connection.h>
#include <lambda_p/core/gather.h>
#include <lambda_p/core/tee.h>
#include <lambda_p/core/call.h>
#include <lambda_p_serialization/analyzer/declaration.h>
#include <lambda_p_serialization/analyzer/full.h>
#include <lambda_p_serialization/analyzer/individual.h>
#include <lambda_p/core/scatter.h>
#include <lambda_p/core/fixed.h>
#include <lambda_p/core/entry.h>
#include <lambda_p/errors/string_error.h>

lambda_p_serialization::analyzer::expression::expression (lambda_p_serialization::analyzer::routine & routine_a, lambda_p_serialization::ast::expression * expression_a, boost::shared_ptr <lambda_p::core::target> target_a, boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a)
	: routine (routine_a),
	target (target_a),
	position (0),
	errors (errors_a),
	tee (new lambda_p::core::tee),
	call (new lambda_p::core::call (tee, errors_a)),
	gather (new lambda_p::core::gather (call))
{
	if (!expression_a->values.empty ())
	{
		if (expression_a->full_name.empty () && expression_a->individual_names.empty ())
		{
			tee->targets.push_back (target);
		}
		else
		{
			auto fixed (boost::shared_ptr <lambda_p::core::fixed> (new lambda_p::core::fixed));
			fixed->target->targets.push_back (target);
			routine.entry->fixed.push_back (fixed);
			if (!expression_a->full_name.empty ())
			{
				routine (expression_a->full_name, boost::shared_ptr <lambda_p_serialization::analyzer::declaration> (new lambda_p_serialization::analyzer::full (tee)));
			}
			if (!expression_a->individual_names.empty ())
			{
				boost::shared_ptr <lambda_p::core::scatter> scatter (new lambda_p::core::scatter (expression_a->individual_names.size (), errors));
				tee->targets.push_back (scatter);
				size_t position_l (0);
				for (auto i (expression_a->individual_names.begin ()), j (expression_a->individual_names.end ()); i != j; ++i, ++position_l)
				{
					routine (*i, boost::shared_ptr <lambda_p_serialization::analyzer::declaration> (new lambda_p_serialization::analyzer::individual (scatter, position_l)));
				}
			}
		}
		for (auto i (expression_a->values.begin ()), j (expression_a->values.end ()); i != j; ++i)
		{
			(*(*i)) (this);
			++position;
			gather->increment ();
		}
	}
	else
	{
		errors (boost::shared_ptr <lambda_p::errors::string_error> (new lambda_p::errors::string_error (std::wstring (L"Expression has no target"))));
	}
}

void lambda_p_serialization::analyzer::expression::operator () (lambda_p_serialization::ast::expression * expression_a)
{
	auto connection (boost::shared_ptr <lambda_p::core::target> (new lambda_p::core::connection (gather, position)));
	lambda_p_serialization::analyzer::expression expression (routine, expression_a, connection, errors);
}

void lambda_p_serialization::analyzer::expression::operator () (lambda_p_serialization::ast::identifier * identifier_a)
{
	auto connection (boost::shared_ptr <lambda_p::core::target> (new lambda_p::core::connection (gather, position)));
	auto existing (routine.declarations.find (identifier_a->string));
	if (existing != routine.declarations.end ())
	{
		(*existing->second) (connection);
	}
	else
	{
		routine.unresolved.insert (std::multimap <std::wstring, boost::shared_ptr <lambda_p::core::target>>::value_type (identifier_a->string, connection));
	}
}