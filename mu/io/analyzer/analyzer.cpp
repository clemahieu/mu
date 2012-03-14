#include <mu/io/analyzer/analyzer.h>

#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/analyzer/routine.h>
#include <mu/core/errors/string_error.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/analyzer/resolver.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/core/routine.h>
#include <mu/io/debugging/cluster.h>
#include <mu/core/expression.h>
#include <mu/io/ast/end.h>
#include <mu/io/debugging/routine.h>
#include <mu/io/debugging/error.h>
#include <mu/io/debugging/mapping.h>

#include <sstream>

#include <boost/make_shared.hpp>

mu::io::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <mu::core::cluster>, boost::shared_ptr <mu::io::debugging::mapping>)> target_a, boost::shared_ptr <mu::core::errors::error_target> errors_a)
	: extensions (new mu::io::analyzer::extensions::extensions),
	target (target_a),
	errors (errors_a),
	cluster (new mu::core::cluster),
	cluster_info (new mu::io::debugging::cluster),
	mapping (new mu::io::debugging::mapping)
{
	mapping->nodes [cluster] = cluster_info;
}

mu::io::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <mu::core::cluster>, boost::shared_ptr <mu::io::debugging::mapping>)> target_a, boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: extensions (extensions_a),
	target (target_a),
	errors (errors_a),
	cluster (new mu::core::cluster),
	cluster_info (new mu::io::debugging::cluster),
	mapping (new mu::io::debugging::mapping)
{
	mapping->nodes [cluster] = cluster_info;
}

void mu::io::analyzer::analyzer::input (boost::shared_ptr <mu::io::ast::node> node_a)
{
	(*node_a) (this);
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::parameters * parameters_a)
{
	(*errors) (L"Analyzer not expecting parameters");
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::expression * expression_a)
{
	if (cluster->routines.empty ())
	{
		cluster_info->context.first = expression_a->context.first;
	}
	mu::io::analyzer::routine (*this, expression_a);
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::identifier * identifier_a)
{
	(*errors) (L"Analyzer not expecting identifiers");
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::end * end_a)
{	
	cluster_info->context.last = end_a->context.last;
	if (unresolved.empty ())
	{
		if (!(*errors) ())
		{
			target (cluster, mapping);
		}
		else
		{
			(*errors) (L"Not generating cluster due to other errors");
		}
	}
	else
	{
		for (auto i (unresolved.begin ()), j (unresolved.end ()); i != j; ++i)
		{
			std::wstringstream message;
			message << L"Unresolved identifier: ";
			message << i->first;
			(*errors) (boost::make_shared <mu::io::debugging::error> (boost::make_shared <mu::core::errors::string_error> (message.str ()), i->second.second));
		}
	}
}

void mu::io::analyzer::analyzer::mark_used (std::wstring name_a, boost::shared_ptr <mu::io::debugging::node> node_info_a)
{
	used_names.insert (std::multimap <std::wstring, boost::shared_ptr <mu::io::debugging::node>>::value_type (name_a, node_info_a));
}

void mu::io::analyzer::analyzer::back_resolve (std::wstring name_a, boost::shared_ptr <mu::core::node> node_a, boost::shared_ptr <mu::io::debugging::node> node_info_a)
{
	for (auto i (unresolved.find (name_a)), j (unresolved.end ()); i != j && i->first == name_a; ++i)
	{
		(*(i->second).first) (node_a, node_info_a);
	}
	unresolved.erase (name_a);
}

void mu::io::analyzer::analyzer::resolve_routine (std::wstring name_a, boost::shared_ptr <mu::core::routine> routine_a, boost::shared_ptr <mu::io::debugging::routine> routine_info_a)
{
	assert (!name_a.empty ());
	auto keyword (extensions->extensions_m.find (name_a));
	if (keyword == extensions->extensions_m.end ())
	{
		auto existing (used_names.find (name_a));
		if (existing == used_names.end ())
		{
			mark_used (name_a, routine_info_a);
			assert (cluster->names.find (name_a) == cluster->names.end ());
			cluster->routines.push_back (routine_a);
			cluster->names [name_a] = routine_a;
			assert (cluster_info->names.find (name_a) == cluster_info->names.end ());
			cluster_info->routines.push_back (routine_info_a);
			cluster_info->names [name_a] = routine_info_a;
			back_resolve (name_a, routine_a, routine_info_a);
		}
		else
		{
			for (; existing != used_names.end () && existing->first == name_a; ++existing)
			{
				std::wstringstream message;
				message << L"Routine name: ";
				message << name_a;
				message << L" collides with usage at: ";
				message << existing->second->context.string ();
				(*errors) (message.str ());
			}
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Routine named: ";
		message << name_a;
		message << L" is a keyword";
		(*errors) (message.str ());
	}
}