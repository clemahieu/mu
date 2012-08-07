#include <mu/script/analyzer/operation.h>

#include <mu/script/extensions/node.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/io/keywording/global.h>
#include <mu/script/extensions/node.h>
#include <mu/io/keywording/state.h>
#include <mu/io/ast/expression.h>
#include <mu/script/check.h>
#include <mu/core/errors/error_target.h>

#include <boost/bind.hpp>

bool mu::script::analyzer::operation::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::io::ast::cluster> (context_a));
	if (result)
	{
		auto ast (static_cast <mu::io::ast::cluster *> (context_a.parameters (0)));
		auto result (core (context_a, ast));
	}
	return result;
}

mu::core::cluster * mu::script::analyzer::operation::core (mu::script::context & context_a, mu::io::ast::cluster * ast)
{
	mu::core::cluster * result;
	mu::io::analyzer::analyzer analyzer (boost::bind (&mu::script::analyzer::operation::build, this, &result, _1), context_a.errors);
	analyzer.input (ast);
	return result;
}

void mu::script::analyzer::operation::build (mu::core::cluster ** result_a, mu::core::cluster * cluster_a)
{
	*result_a = cluster_a;
}