#include "expression.h"

#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/call.h>
#include <lambda_p/set.h>
#include <lambda_p/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/analyzer/resolver.h>
#include <lambda_p_io/analyzer/extension.h>
#include <lambda_p/reference.h>

lambda_p_io::analyzer::expression::expression (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a, lambda_p::expression & target_a)
	: routine (routine_a),
	expression_m (expression_a),
	position (0)
{
	if (expression_a->full_name.empty () && expression_a->individual_names.empty ())
	{
		boost::shared_ptr <lambda_p::call> call_l (new lambda_p::call);
		target_a.dependencies.push_back (call_l);
		self = call_l;
	}
	else
	{
		boost::shared_ptr <lambda_p::set> set_l (new lambda_p::set);
		self = set_l;
		if (!expression_a->full_name.empty ())
		{
			routine_a (expression_a->full_name, set_l);
		}
		for (size_t i (0), j (expression_a->individual_names.size ()); i != j; ++i)
		{
			routine_a (expression_a->individual_names [i], boost::shared_ptr <lambda_p::reference> (new lambda_p::reference (set_l, i)));
		}
	}
	for (auto end (expression_a->values.size ()); position != end; ++position)
	{
		(*expression_a->values [position]) (this);
	}
}

void lambda_p_io::analyzer::expression::operator () (lambda_p_io::ast::parameters * parameters_a)
{
	self->dependencies.push_back (routine.routine_m->parameters);
}

void lambda_p_io::analyzer::expression::operator () (lambda_p_io::ast::expression * expression_a)
{
	lambda_p_io::analyzer::expression expression (routine, expression_a, *self);
}

void lambda_p_io::analyzer::expression::operator () (lambda_p_io::ast::identifier * identifier_a)
{
	auto keyword (routine.analyzer.extensions.find (identifier_a->string));
	if (keyword == routine.analyzer.extensions.end ())
	{
		auto existing (routine.declarations.find (identifier_a->string));
		if (existing != routine.declarations.end ())
		{
			self->dependencies.push_back (existing->second);
		}
		else
		{
			self->dependencies.push_back (boost::shared_ptr <lambda_p::expression> ());
			routine.unresolved.insert (std::multimap <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::resolver>>::value_type (identifier_a->string, boost::shared_ptr <lambda_p_io::analyzer::resolver> (new lambda_p_io::analyzer::resolver (self, self->dependencies.size () - 1))));
		}
	}
	else
	{
		(*keyword->second) (*this);
	}
}