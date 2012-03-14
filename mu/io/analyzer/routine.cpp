#include <mu/io/analyzer/routine.h>

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
#include <mu/io/debugging/routine.h>
#include <mu/io/debugging/cluster.h>
#include <mu/io/debugging/expression.h>
#include <mu/io/debugging/mapping.h>

#include <sstream>

#include <boost/make_shared.hpp>

mu::io::analyzer::routine::routine (mu::io::analyzer::analyzer & analyzer_a, mu::io::ast::expression * expression_a)
	: analyzer (analyzer_a),
	routine_m (new mu::core::routine),
	routine_info (new mu::io::debugging::routine)
{
	analyzer_a.mapping->nodes [routine_m] = routine_info;
	routine_info->context = expression_a->context;
	if (expression_a->individual_names.empty ())
	{
		auto name (expression_a->full_name->string);
		if (!name.empty ())
		{
			expression_a->full_name->string.clear ();
		}
		auto expression_l (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
		auto expression_info (boost::make_shared <mu::io::debugging::expression> ());
		analyzer_a.mapping->nodes [expression_l] = expression_info;
		expression_info->context = expression_a->context;
		mu::io::analyzer::expression expression (*this, expression_a, expression_l, expression_info);
		routine_m->body = expression_l;
		routine_info->body = expression_info;
		if (!name.empty ())
		{
			analyzer.resolve_routine (name, routine_m, routine_info);
		}
		else
		{
			analyzer.cluster->routines.push_back (routine_m);
			analyzer.cluster_info->routines.push_back (routine_info);
		}
	}
	else
	{
		(*analyzer_a.errors) (L"Routines cannot have individual names");
	}
}

void mu::io::analyzer::routine::resolve_local (std::wstring identifier, boost::shared_ptr <mu::core::node> node, boost::shared_ptr <mu::io::debugging::node> node_info_a)
{
	if (analyzer.extensions->extensions_m.find (identifier) == analyzer.extensions->extensions_m.end ())
	{
		if (analyzer.cluster->names.find (identifier) == analyzer.cluster->names.end ())
		{
			if (declarations.find (identifier) == declarations.end ())
			{
				analyzer.mark_used (identifier, node_info_a);
				declarations.insert (std::map <std::wstring, std::pair <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::io::debugging::node>>>::value_type (identifier, std::pair <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::io::debugging::node>> (node, node_info_a)));
				analyzer.back_resolve (identifier, node, node_info_a);
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