#include <mu/io/analyzer/analyzer.h>

#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>
#include <mu/io/analyzer/routine.h>
#include <mu/core/errors/string_error.h>
#include <mu/core/errors/error_target.h>
#include <mu/io/analyzer/resolver.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/io/ast/cluster.h>

#include <sstream>

#include <gc_cpp.h>

mu::io::analyzer::analyzer::analyzer (boost::function <void (mu::core::cluster *)> target_a, mu::core::errors::error_target & errors_a)
	: target (target_a),
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
    names.finalize (errors);
    if (!errors ())
    {
        target (cluster);
    }
    else
    {
        errors (U"Not generating cluster due to errors");
    }
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::cluster * cluster_a)
{
	errors (U"Analyzer not expecting cluster");
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::parameters * parameters_a)
{
	errors (U"Analyzer not expecting parameters");
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::expression * expression_a)
{
	mu::io::analyzer::routine (*this, expression_a);
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::identifier * identifier_a)
{
	errors (U"Analyzer not expecting identifiers");
}

void mu::io::analyzer::analyzer::operator () (mu::io::ast::value * value_a)
{
	errors (U"Analyzer not expecting values");
}