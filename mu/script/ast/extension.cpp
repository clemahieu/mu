#include <mu/script/ast/extension.h>

#include <mu/core/errors/error_target.h>
#include <mu/io/analyzer/expression.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/core/expression.h>
#include <mu/io/ast/cluster.h>

#include <gc_cpp.h>

void mu::script::ast::extension::operator () (mu::core::errors::error_target * errors_a, mu::io::analyzer::expression & expression_a)
{
	size_t position (expression_a.position + 1);
	if (position < expression_a.expression_m->values.size ())
	{
		expression_a.position = position;
		auto result (core (errors_a, expression_a.expression_m->values [position]));
		expression_a.self->dependencies.push_back (result);
	}
	else
	{
		(*errors_a) (L"AST extension requires at least one argument");
	}
}

mu::io::ast::cluster * mu::script::ast::extension::core (mu::core::errors::error_target * errors_a, mu::io::ast::node * node_a)
{
	auto result (new (GC) mu::io::ast::cluster);
	auto value (dynamic_cast <mu::io::ast::expression *> (node_a));
	if (value != nullptr)
	{
		if (value->full_name->string.empty () && value->individual_names.empty ())
		{
			bool good (true);
			for (auto i (value->values.begin ()), j (value->values.end ()); i != j && good; ++i)
			{
				auto expression (dynamic_cast <mu::io::ast::expression *> (*i));
				if (expression != nullptr)
				{
					result->expressions.push_back (expression);
				}
				else
				{
					good = false;
					(*errors_a) (L"AST argument must only contain expressions");
				}
			}
		}
		else
		{
			(*errors_a) (L"AST extension requires top level to not be named");
		}
	}
	else
	{
		(*errors_a) (L"AST extension requires argument to be an expression");
	}
	return result;
}