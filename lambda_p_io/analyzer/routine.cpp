#include "routine.h"

#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p/errors/string_error.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/routine.h>
#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/analyzer/resolver.h>
#include <lambda_p/expression.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>
#include <lambda_p_io/ast/identifier.h>

#include <sstream>

lambda_p_io::analyzer::routine::routine (lambda_p_io::analyzer::analyzer & analyzer_a, lambda_p_io::ast::expression * expression_a)
	: analyzer (analyzer_a),
	routine_m (new lambda_p::routine (lambda_p::context (expression_a->context.first, expression_a->context.first)))
{
	if (expression_a->individual_names.empty ())
	{
		auto name (expression_a->full_name->string);
		if (!name.empty ())
		{
			expression_a->full_name->string.clear ();
		}
		auto expression_l (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (expression_a->context)));
		lambda_p_io::analyzer::expression expression (*this, expression_a, expression_l);
		routine_m->body = expression_l;
		if (!name.empty ())
		{
			analyzer.resolve_routine (name, routine_m, expression_a->context);
		}
		else
		{
			analyzer.cluster->routines.push_back (routine_m);
		}
	}
	else
	{
		(*analyzer_a.errors) (L"Routines cannot have individual names");
	}
}

void lambda_p_io::analyzer::routine::resolve_local (std::wstring identifier, boost::shared_ptr <lambda_p::node> node, lambda_p::context context_a)
{
	if (analyzer.extensions->extensions_m.find (identifier) == analyzer.extensions->extensions_m.end ())
	{
		if (analyzer.cluster->names.find (identifier) == analyzer.cluster->names.end ())
		{
			if (declarations.find (identifier) == declarations.end ())
			{
				analyzer.mark_used (identifier, context_a);
				declarations.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::node>>::value_type (identifier, node));
				analyzer.back_resolve (identifier, node);
			}
			else
			{
				std::wstringstream message;
				message << L"The identifier: ";
				message << identifier;
				message << L" collides with another local declaration";
				(*analyzer.errors) (message.str ());
			}
		}
		else
		{
			std::wstringstream message;
			message << L"The identifier: ";
			message << identifier;
			message << L" collides with a routine name in the cluster";
			(*analyzer.errors) (message.str ());
		}
	}
	else
	{
		std::wstringstream message;
		message << L"The identifier: ";
		message << identifier;
		message << L" is a keyword";
		(*analyzer.errors) (message.str ());
	}
}