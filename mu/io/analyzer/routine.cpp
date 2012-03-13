#include "routine.h"

#include <mu/io/ast/expression.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/core/errors/string_error.h>
#include <mu/core/errors/error_list.h>
#include <mu/core/routine.h>
#include <mu/io/analyzer/expression.h>
#include <mu/io/analyzer/resolver.h>
#include <mu/core/expression.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/ast/identifier.h>

#include <sstream>

mu::io::analyzer::routine::routine (mu::io::analyzer::analyzer & analyzer_a, mu::io::ast::expression * expression_a)
	: analyzer (analyzer_a),
	routine_m (new mu::core::routine (mu::core::context (expression_a->context.first, expression_a->context.first)))
{
	if (expression_a->individual_names.empty ())
	{
		auto name (expression_a->full_name->string);
		if (!name.empty ())
		{
			expression_a->full_name->string.clear ();
		}
		auto expression_l (boost::shared_ptr <mu::core::expression> (new mu::core::expression (expression_a->context)));
		mu::io::analyzer::expression expression (*this, expression_a, expression_l);
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

void mu::io::analyzer::routine::resolve_local (std::wstring identifier, boost::shared_ptr <mu::core::node> node, mu::core::context context_a)
{
	if (analyzer.extensions->extensions_m.find (identifier) == analyzer.extensions->extensions_m.end ())
	{
		if (analyzer.cluster->names.find (identifier) == analyzer.cluster->names.end ())
		{
			if (declarations.find (identifier) == declarations.end ())
			{
				analyzer.mark_used (identifier, context_a);
				declarations.insert (std::map <std::wstring, boost::shared_ptr <mu::core::node>>::value_type (identifier, node));
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