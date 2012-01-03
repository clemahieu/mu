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

#include <sstream>

lambda_p_serialization::analyzer::routine::routine (lambda_p_serialization::analyzer::analyzer & analyzer_a, lambda_p_serialization::ast::expression * expression_a, std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::analyzer::declaration>> declarations_a, boost::function <void (boost::shared_ptr <lambda_p::errors::error>)> errors_a)
	: entry (new lambda_p::core::entry (errors_a)),
	pipe (new lambda_p::core::pipe),
	declarations (declarations_a)
{
	if (declarations.find (std::wstring (L"~")) == declarations.end ())
	{
		declarations.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_serialization::analyzer::declaration>>::value_type (std::wstring (L"~"), boost::shared_ptr <lambda_p_serialization::analyzer::declaration> (new lambda_p_serialization::analyzer::full (entry->next))));
		if (expression_a->individual_names.empty () && expression_a->full_name.empty ())
		{
			lambda_p_serialization::analyzer::expression expression (*this, expression_a, pipe, errors_a);
			if (unresolved.empty ())
			{
				auto routine (boost::shared_ptr <lambda_p::core::routine> (new lambda_p::core::routine (entry, pipe, errors_a)));
				analyzer_a.target (routine);
			}
			else
			{
				for (auto i (unresolved.begin ()), j (unresolved.end ()); i != j; ++i)
				{
					std::wstringstream message;
					message << L"Unresolved identifier: ";
					message << i->first;
					analyzer_a.errors (boost::shared_ptr <lambda_p::errors::error> (new lambda_p::errors::string_error (message.str ())));
				}
			}
		}
		else
		{
			analyzer_a.errors (boost::shared_ptr <lambda_p::errors::error> (new lambda_p::errors::string_error (std::wstring (L"Top level routine cannot have individual or a full name"))));
		}
	}
	else
	{
		analyzer_a.errors (boost::shared_ptr <lambda_p::errors::error> (new lambda_p::errors::string_error (std::wstring (L"Identifier ~ is already declared"))));
	}
}