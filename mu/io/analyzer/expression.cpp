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

#include <boost/make_shared.hpp>

mu::io::analyzer::expression::expression (mu::io::analyzer::routine & routine_a, mu::io::ast::expression * expression_a, boost::shared_ptr <mu::core::expression> self_a, mu::io::debugging::expression * self_info_a)
	: routine (routine_a),
	expression_m (expression_a),
	self (self_a),
	position (0),
	self_info (self_info_a)
{
	if (!expression_a->full_name->string.empty ())
	{
		routine_a.resolve_local (expression_a->full_name->string, self, new mu::io::debugging::node (expression_a->full_name->context));
	}
	for (size_t i (0), j (expression_a->individual_names.size ()); i != j; ++i)
	{
		routine_a.resolve_local (expression_a->individual_names [i]->string, boost::shared_ptr <mu::core::reference> (new mu::core::reference (self, i)), new mu::io::debugging::node (expression_a->individual_names [i]->context));
	}
	for (auto end (expression_a->values.size ()); position < end; ++position)
	{
		(*expression_a->values [position]) (this);
	}
}

void mu::io::analyzer::expression::operator () (mu::io::ast::parameters * parameters_a)
{
	self->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	self_info->dependencies.push_back (new mu::io::debugging::node (parameters_a->context));
}

void mu::io::analyzer::expression::operator () (mu::io::ast::expression * expression_a)
{
	auto expression_l (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	auto expression_info (new mu::io::debugging::expression);
	expression_info->context = expression_a->context;
	expression_info->routine = self_info->routine;
	mu::io::analyzer::expression expression (routine, expression_a, expression_l, expression_info);
	if (expression_a->full_name->string.empty () && expression_a->individual_names.empty ())
	{
		self->dependencies.push_back (expression.self);
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
				self_info->dependencies.push_back (nullptr);
				routine.analyzer.unresolved.insert (std::multimap <std::wstring, std::pair <boost::shared_ptr <mu::io::analyzer::resolver>, mu::core::context>>::value_type (identifier_a->string, std::pair <boost::shared_ptr <mu::io::analyzer::resolver>, mu::core::context> (boost::shared_ptr <mu::io::analyzer::resolver> (new mu::io::analyzer::resolver (self, self_info, self->dependencies.size () - 1)), identifier_a->context)));
			}
			else
			{
				self->dependencies.push_back (routine_l->second);
				auto info (routine.analyzer.cluster_info->mapping.find (routine_l->second));
				assert (info != routine.analyzer.cluster_info->mapping.end ());
				self_info->dependencies.push_back (info->second);
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

void mu::io::analyzer::expression::operator () (mu::io::ast::end * end_a)
{	
	(*routine.analyzer.errors) (L"Expression not expecting end");
}