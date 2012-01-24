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

#include <sstream>

lambda_p_io::analyzer::routine::routine (lambda_p_io::analyzer::analyzer & analyzer_a, lambda_p_io::ast::expression * expression_a)
	: analyzer (analyzer_a),
	routine_m (new lambda_p::routine (lambda_p::context (expression_a->context.first, expression_a->context.first)))
{
	if (expression_a->individual_names.empty ())
	{
		if (expression_a->full_name.empty ())
		{
			expression_a->full_name = std::wstring (L"anonymous");
		}
		auto expression_l (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (expression_a->context)));
		lambda_p_io::analyzer::expression expression (*this, expression_a, expression_l);
		routine_m->body = expression_l;
		if (unresolved.empty ())
		{
			if (!(*analyzer.errors) ())
			{
				analyzer_a.target (routine_m);
			}
			else
			{
				(*analyzer_a.errors) (L"Not generating routine due to other errors");
			}
		}
		else
		{
			for (auto i (unresolved.begin ()), j (unresolved.end ()); i != j; ++i)
			{
				std::wstringstream message;
				message << L"Unresolved identifier: ";
				message << i->first;
				(*analyzer_a.errors) (message.str ());
			}
		}
	}
	else
	{
		(*analyzer_a.errors) (L"Top level routine cannot have individual names");
	}
}

void lambda_p_io::analyzer::routine::operator () (std::wstring identifier, boost::shared_ptr <lambda_p::node> node)
{
	if (analyzer.extensions->extensions_m.find (identifier) == analyzer.extensions->extensions_m.end ())
	{
		declarations.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::node>>::value_type (identifier, node));
		for (auto i (unresolved.find (identifier)), j (unresolved.end ()); i != j && i->first == identifier; ++i)
		{
			(*i->second) (node);
		}
		unresolved.erase (identifier);
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