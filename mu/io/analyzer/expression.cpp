#include <mu/io/analyzer/expression.h>

#include <mu/io/analyzer/routine.h>
#include <mu/io/ast/expression.h>
#include <mu/core/expression.h>
#include <mu/core/routine.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/analyzer/resolver.h>
#include <mu/io/analyzer/extensions/extension.h>
#include <mu/core/reference.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/core/errors/error_context.h>
#include <mu/core/parameters.h>
#include <mu/io/debugging/expression.h>
#include <mu/io/ast/parameters.h>
#include <mu/io/debugging/node.h>
#include <mu/io/debugging/cluster.h>
#include <mu/io/debugging/routine.h>
#include <mu/io/debugging/mapping.h>

#include <boost/make_shared.hpp>

mu::io::analyzer::expression::expression (mu::io::analyzer::routine & routine_a, mu::io::ast::expression * expression_a, boost::shared_ptr <mu::core::expression> self_a, boost::shared_ptr <mu::io::debugging::expression> self_info_a)
	: routine (routine_a),
	expression_m (expression_a),
	self (self_a),
	position (0),
	self_info (self_info_a)
{
	if (!expression_a->full_name->string.empty ())
	{
		routine_a.resolve_local (expression_a->full_name->string, self, self_info);
	}
	for (size_t i (0), j (expression_a->individual_names.size ()); i != j; ++i)
	{
		auto reference (boost::make_shared <mu::core::reference> (self, i));
		auto reference_info (boost::make_shared <mu::io::debugging::node> (expression_a->individual_names [i]->context));
		routine_a.analyzer.mapping->nodes [reference] = reference_info;
		routine_a.resolve_local (expression_a->individual_names [i]->string, reference, reference_info);
	}
	for (auto end (expression_a->values.size ()); position < end; ++position)
	{
		(*expression_a->values [position]) (this);
	}
}

void mu::io::analyzer::expression::operator () (mu::io::ast::parameters * parameters_a)
{
	auto parameters_l (boost::make_shared <mu::core::parameters> ());
	self->dependencies.push_back (parameters_l);
	auto parameters_info (boost::make_shared <mu::io::debugging::node> (parameters_a->context));
	self_info->dependencies.push_back (parameters_info);
	routine.analyzer.mapping->nodes [parameters_l] = parameters_info;
}

void mu::io::analyzer::expression::operator () (mu::io::ast::expression * expression_a)
{
	auto expression_l (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	auto expression_info (boost::make_shared <mu::io::debugging::expression> ());
	routine.analyzer.mapping->nodes [expression_l] = expression_info;
	expression_info->context = expression_a->context;
	mu::io::analyzer::expression expression (routine, expression_a, expression_l, expression_info);
	if (expression_a->full_name->string.empty () && expression_a->individual_names.empty ())
	{
		self->dependencies.push_back (expression.self);
		self_info->dependencies.push_back (expression.self_info);
	}
	else
	{
		// When naming we don't pass the expression results to the parent
	}
}

void mu::io::analyzer::expression::operator () (mu::io::ast::identifier * identifier_a)
{
	auto keyword (routine.analyzer.extensions->extensions_m.find (identifier_a->string));
	if (keyword == routine.analyzer.extensions->extensions_m.end ())
	{
		auto local (routine.declarations.find (identifier_a->string));
		if (local == routine.declarations.end ())
		{
			auto routine_l (routine.analyzer.cluster->names.find (identifier_a->string));
			if (routine_l == routine.analyzer.cluster->names.end ())
			{
				self->dependencies.push_back (boost::shared_ptr <mu::core::expression> ());
				self_info->dependencies.push_back (boost::shared_ptr <mu::io::debugging::node> ());
				routine.analyzer.unresolved.insert (std::multimap <std::wstring, std::pair <boost::shared_ptr <mu::io::analyzer::resolver>, mu::io::debugging::context>>::value_type (identifier_a->string, std::pair <boost::shared_ptr <mu::io::analyzer::resolver>, mu::io::debugging::context> (boost::shared_ptr <mu::io::analyzer::resolver> (new mu::io::analyzer::resolver (self, self->dependencies.size () - 1)), identifier_a->context)));
			}
			else
			{
				self->dependencies.push_back (routine_l->second);
				auto routine_info (routine.analyzer.cluster_info->names.find (identifier_a->string));
				assert (routine_info != routine.analyzer.cluster_info->names.end ());
				self_info->dependencies.push_back (routine_info->second);
			}
		}
		else
		{
			assert (routine.analyzer.cluster->names.find (identifier_a->string) == routine.analyzer.cluster->names.end ());
			self->dependencies.push_back (local->second.first);
			self_info->dependencies.push_back (local->second.second);
		}
	}
	else
	{
		assert (routine.declarations.find (identifier_a->string) == routine.declarations.end ());
		assert (routine.analyzer.cluster->names.find (identifier_a->string) == routine.analyzer.cluster->names.end ());
		auto errors_l (boost::make_shared <mu::core::errors::error_context> (routine.analyzer.errors, identifier_a->context));
		(*keyword->second) (errors_l, *this);
	}
}

void mu::io::analyzer::expression::operator () (mu::io::ast::cluster * cluster_a)
{
	(*routine.analyzer.errors) (L"Expression not expecting cluster");
}