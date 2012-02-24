#include "analyzer.h"

#include <io/ast/expression.h>
#include <io/ast/identifier.h>
#include <io/analyzer/routine.h>
#include <core/errors/string_error.h>
#include <core/errors/error_target.h>
#include <io/analyzer/resolver.h>
#include <io/analyzer/extensions/extensions.h>
#include <core/routine.h>

#include <sstream>

#include <boost/make_shared.hpp>

mu::io::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <mu::core::cluster>)> target_a, boost::shared_ptr <mu::core::errors::error_target> errors_a)
	: target (target_a),
	errors (errors_a),
	extensions (new mu::io::analyzer::extensions::extensions),
	cluster (new mu::core::cluster)
{
}

mu::io::analyzer::analyzer::analyzer (boost::function <void (boost::shared_ptr <mu::core::cluster>)> target_a, boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: target (target_a),
	errors (errors_a),
	extensions (extensions_a),
	cluster (new mu::core::cluster)
{
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
	mu::io::analyzer::routine (*this, expression_a);
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::identifier * identifier_a)
{
	(*errors) (L"Analyzer not expecting identifiers");
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::end * end_a)
{	
	if (unresolved.empty ())
	{
		if (!(*errors) ())
		{
			target (cluster);
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
			(*errors) (message.str (), i->second.second);
		}
	}
}

void mu::io::analyzer::analyzer::mark_used (std::wstring name_a, mu::core::context context_a)
{
	used_names.insert (std::multimap <std::wstring, mu::core::context>::value_type (name_a, context_a));
}

void mu::io::analyzer::analyzer::back_resolve (std::wstring name_a, boost::shared_ptr <mu::core::node> node_a)
{
	for (auto i (unresolved.find (name_a)), j (unresolved.end ()); i != j && i->first == name_a; ++i)
	{
		(*(i->second).first) (node_a);
	}
	unresolved.erase (name_a);
}

void mu::io::analyzer::analyzer::resolve_routine (std::wstring name_a, boost::shared_ptr <mu::core::routine> routine_a, mu::core::context context_a)
{
	assert (!name_a.empty ());
	auto keyword (extensions->extensions_m.find (name_a));
	if (keyword == extensions->extensions_m.end ())
	{
		auto existing (used_names.find (name_a));
		if (existing == used_names.end ())
		{
			mark_used (name_a, context_a);
			assert (cluster->names.find (name_a) == cluster->names.end ());
			cluster->routines.push_back (routine_a);
			cluster->names [name_a] = routine_a;
			back_resolve (name_a, routine_a);
		}
		else
		{
			for (; existing != used_names.end () && existing->first == name_a; ++existing)
			{
				std::wstringstream message;
				message << L"Routine name: ";
				message << name_a;
				message << L" collides with usage at: ";
				message << existing->second.string ();
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