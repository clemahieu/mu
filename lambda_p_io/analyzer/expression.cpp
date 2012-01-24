#include "expression.h"

#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p/expression.h>
#include <lambda_p/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/analyzer/resolver.h>
#include <lambda_p_io/analyzer/extensions/extension.h>
#include <lambda_p/reference.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>

lambda_p_io::analyzer::expression::expression (lambda_p_io::analyzer::routine & routine_a, lambda_p_io::ast::expression * expression_a, boost::shared_ptr <lambda_p::expression> self_a)
	: routine (routine_a),
	expression_m (expression_a),
	position (0),
	self (self_a)
{
	if (!expression_a->full_name->string.empty ())
	{
		routine_a (expression_a->full_name->string, self);
	}
	for (size_t i (0), j (expression_a->individual_names.size ()); i != j; ++i)
	{
		routine_a (expression_a->individual_names [i]->string, boost::shared_ptr <lambda_p::reference> (new lambda_p::reference (self, i)));
	}
	for (auto end (expression_a->values.size ()); position < end; ++position)
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
	auto expression_l (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (expression_a->context)));
	lambda_p_io::analyzer::expression expression (routine, expression_a, expression_l);
	if (expression_a->full_name->string.empty () && expression_a->individual_names.empty ())
	{
		self->dependencies.push_back (expression.self);
	}
	else
	{
		// When naming we don't pass the expression results to the parent
	}
}

void lambda_p_io::analyzer::expression::operator () (lambda_p_io::ast::identifier * identifier_a)
{
	auto keyword (routine.analyzer.extensions->extensions_m.find (identifier_a->string));
	if (keyword == routine.analyzer.extensions->extensions_m.end ())
	{
		auto existing (routine.declarations.find (identifier_a->string));
		if (existing != routine.declarations.end ())
		{
			self->dependencies.push_back (existing->second);
		}
		else
		{
			self->dependencies.push_back (boost::shared_ptr <lambda_p::expression> ());
			routine.unresolved.insert (std::multimap <std::wstring, std::pair <boost::shared_ptr <lambda_p_io::analyzer::resolver>, lambda_p::context>>::value_type (identifier_a->string, std::pair <boost::shared_ptr <lambda_p_io::analyzer::resolver>, lambda_p::context> (boost::shared_ptr <lambda_p_io::analyzer::resolver> (new lambda_p_io::analyzer::resolver (self, self->dependencies.size () - 1)), identifier_a->context)));
		}
	}
	else
	{
		(*keyword->second) (*this);
	}
}