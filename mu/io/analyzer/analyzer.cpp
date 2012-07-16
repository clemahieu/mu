#include <mu/io/analyzer/analyzer.h>

#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/analyzer/routine.h>
#include <mu/core/errors/string_error.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/analyzer/resolver.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/io/ast/cluster.h>

#include <sstream>

#include <gc_cpp.h>

mu::io::analyzer::analyzer::analyzer (boost::function <void (mu::core::cluster *)> target_a, mu::core::errors::error_target * errors_a)
	: extensions (new (GC) mu::io::analyzer::extensions::extensions),
	target (target_a),
	errors (errors_a),
	cluster (new (GC) mu::core::cluster)
{
}

mu::io::analyzer::analyzer::analyzer (boost::function <void (mu::core::cluster *)> target_a, mu::core::errors::error_target * errors_a, mu::io::analyzer::extensions::extensions * extensions_a)
	: extensions (extensions_a),
	target (target_a),
	errors (errors_a),
	cluster (new (GC) mu::core::cluster)
{
}

void mu::io::analyzer::analyzer::input (mu::io::ast::cluster * node_a)
{
	for (auto i (node_a->expressions.begin ()), j (node_a->expressions.end ()); i != j; ++i)
	{
        auto value (*i);
		(*value) (this);
	}
	if (unresolved.empty ())
	{
		if (!(*errors) ())
		{
			target (cluster);
		}
		else
		{
			(*errors) (U"Not generating cluster due to other errors");
		}
	}
	else
	{
		for (auto i (unresolved.begin ()), j (unresolved.end ()); i != j; ++i)
		{
            mu::stringstream message;
			message << U"Unresolved identifier: ";
			message << i->first;
			(*errors) (new (GC) mu::core::errors::string_error (message.str ()));
		}
	}
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::cluster * cluster_a)
{
	(*errors) (U"Analyzer not expecting cluster");
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::parameters * parameters_a)
{
	(*errors) (U"Analyzer not expecting parameters");
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::expression * expression_a)
{
	mu::io::analyzer::routine (*this, expression_a);
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::identifier * identifier_a)
{
	(*errors) (U"Analyzer not expecting identifiers");
}

void mu::io::analyzer::analyzer::mark_used (mu::string name_a)
{
	used_names.insert (std::set <mu::string>::value_type (name_a));
}

void mu::io::analyzer::analyzer::back_resolve (mu::string name_a, mu::core::node * node_a)
{
	for (auto i (unresolved.find (name_a)), j (unresolved.end ()); i != j && i->first == name_a; ++i)
	{
		(*(i->second).first) (node_a);
	}
	unresolved.erase (name_a);
}

void mu::io::analyzer::analyzer::resolve_routine (mu::string name_a, mu::core::routine * routine_a)
{
	assert (!name_a.empty ());
	auto keyword (extensions->extensions_m.find (name_a));
	if (keyword == extensions->extensions_m.end ())
	{
		auto existing (used_names.find (name_a));
		if (existing == used_names.end ())
		{
			mark_used (name_a);
			assert (cluster->names.find (name_a) == cluster->names.end ());
			cluster->routines.push_back (routine_a);
			cluster->names [name_a] = routine_a;
			back_resolve (name_a, routine_a);
		}
		else
		{
            mu::stringstream message;
			message << L"Routine name: ";
			message << name_a;
			message << L" has already been used";
			(*errors) (message.str ());
		}
	}
	else
	{
        mu::stringstream message;
		message << L"Routine named: ";
		message << name_a;
		message << L" is a keyword";
		(*errors) (message.str ());
	}
}