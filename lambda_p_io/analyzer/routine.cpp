#include "routine.h"

#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p/errors/string_error.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/expression.h>
#include <lambda_p_io/analyzer/resolver.h>
#include <lambda_p_io/analyzer/unresolved.h>

#include <sstream>

lambda_p_io::analyzer::routine::routine (lambda_p_io::analyzer::analyzer & analyzer_a, lambda_p_io::ast::expression * expression_a)
	: analyzer (analyzer_a)
{
	if (expression_a->individual_names.empty () && expression_a->full_name.empty ())
	{
		lambda_p_io::analyzer::expression expression (*this, expression_a);
		if (unresolved.empty ())
		{
			if (!(*analyzer.errors) ())
			{
				analyzer_a.target (expression.result);
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
		(*analyzer_a.errors) (L"Top level routine cannot have individual or a full name");
	}
}

void lambda_p_io::analyzer::routine::operator () (std::wstring identifier, boost::shared_ptr <lambda_p::node> node)
{
	if (analyzer.extensions.find (identifier) == analyzer.extensions.end ())
	{
		declarations.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::node>>::value_type (identifier, node));
		for (auto i (unresolved.begin ()), j (unresolved.end ()); i != j; ++i)
		{
			auto resolver (i->second);
			resolver->expression->dependencies [resolver->index] = node;
			--resolver->unresolved->count;
			if (resolver->unresolved->complete && resolver->unresolved->count == 0) 
			{

			}
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