#include "routine.h"

#include <lambda_p_serialization/ast/expression.h>
#include <lambda_p_serialization/analyzer/analyzer.h>
#include <lambda_p_serialization/analyzer/expression.h>
#include <lambda_p/core/pipe.h>
#include <lambda_p/errors/string_error.h>
#include <lambda_p/core/entry.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_serialization/analyzer/full.h>
#include <lambda_p/core/fixed.h>
#include <lambda_p/core/identity.h>
#include <lambda_p_serialization/analyzer/declaration.h>

#include <sstream>

lambda_p_serialization::analyzer::routine::routine (lambda_p_serialization::analyzer::analyzer & analyzer_a, lambda_p_serialization::ast::expression * expression_a, std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::analyzer::declaration>> declarations_a, boost::shared_ptr <lambda_p::errors::error_target> errors_a)
	: analyzer (analyzer_a),
	entry (new lambda_p::core::entry (errors_a)),
	pipe (new lambda_p::core::pipe),
	declarations (declarations_a)
{
	declarations.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::analyzer::declaration>>::value_type (std::wstring (L"~"), boost::shared_ptr <lambda_p_serialization::analyzer::declaration> (new lambda_p_serialization::analyzer::full (entry->next))));
	auto identity (boost::shared_ptr <lambda_p::core::fixed> (new lambda_p::core::fixed));
	entry->fixed.push_back (identity);
	identity->arguments.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::identity));
	declarations.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::analyzer::declaration>>::value_type (std::wstring (L".identity"), boost::shared_ptr <lambda_p_serialization::analyzer::declaration> (new lambda_p_serialization::analyzer::full (identity->target))));
	if (expression_a->individual_names.empty () && expression_a->full_name.empty ())
	{
		lambda_p_serialization::analyzer::expression expression (*this, expression_a, pipe, errors_a);
		if (unresolved.empty ())
		{
			if (!(*errors_a) ())
			{
				auto routine (boost::shared_ptr <lambda_p::core::routine> (new lambda_p::core::routine (entry, pipe, errors_a)));
				analyzer_a.target (routine);
			}
			else
			{
				(*errors_a) (L"Not generating routine due to other errors");
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

void lambda_p_serialization::analyzer::routine::operator () (std::wstring identifier, boost::shared_ptr <lambda_p_serialization::analyzer::declaration> declaration)
{
	declarations.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::analyzer::declaration>>::value_type (identifier, declaration));
	for (auto i (unresolved.find (identifier)), j (unresolved.end ()); i != j; ++i)
	{
		(*declaration) (i->second);
	}
	unresolved.erase (identifier);
}