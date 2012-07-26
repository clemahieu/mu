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
#include <mu/io/ast/parameters.h>

#include <gc_cpp.h>

mu::io::analyzer::expression::expression (mu::io::analyzer::routine & routine_a, mu::io::ast::expression * expression_a, mu::core::expression * self_a)
	: routine (routine_a),
	expression_m (expression_a),
	self (self_a),
	position (0)
{
	if (!expression_a->full_name->string.empty ())
	{
		routine_a.analyzer.names.insert_local (routine_a.analyzer.errors, expression_a->full_name->string, self_a);
	}
	for (size_t i (0), j (expression_a->individual_names.size ()); i != j; ++i)
	{
		auto reference (new (GC) mu::core::reference (self, i));
        routine_a.analyzer.names.insert_local (routine_a.analyzer.errors, expression_a->individual_names [i]->string, reference);
	}
	for (auto end (expression_a->values.size ()); position < end; ++position)
	{
        auto value (expression_a->values [position]);
		(*value) (this);
	}
}

void mu::io::analyzer::expression::operator () (mu::io::ast::parameters * parameters_a)
{
	auto parameters_l (new (GC) mu::core::parameters);
	self->dependencies.push_back (parameters_l);
}

void mu::io::analyzer::expression::operator () (mu::io::ast::expression * expression_a)
{
	auto expression_l (new (GC) mu::core::expression);
	mu::io::analyzer::expression expression (routine, expression_a, expression_l);
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
	auto keyword ((*routine.analyzer.extensions) (identifier_a->string));
	if (keyword == nullptr)
	{
        routine.analyzer.names.fill_reference (identifier_a->string, identifier_a->context, *self);
	}
	else
	{
		auto errors_l (new (GC) mu::core::errors::error_context (routine.analyzer.errors, identifier_a->context));
		(*keyword) (errors_l, *this, mu::string ());
	}
}

void mu::io::analyzer::expression::operator () (mu::io::ast::cluster * cluster_a)
{
	(*routine.analyzer.errors) (U"Expression not expecting cluster");
}