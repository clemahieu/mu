#include <mu/script/analyzer/operation.h>

#include <mu/script/extensions/node.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/script_io/cluster.h>
#include <mu/script/cluster/node.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/runtime/routine.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/end.h>
#include <mu/script/check.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void mu::script::analyzer::operation::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::extensions::node, mu::io::ast::cluster> () (context_a))
	{
		auto extensions (boost::static_pointer_cast <mu::script::extensions::node> (context_a.parameters [0]));
		auto ast (boost::static_pointer_cast <mu::io::ast::cluster> (context_a.parameters [1]));
		auto result (core (context_a, extensions, ast));
	}
}

boost::shared_ptr <mu::script::cluster::node> mu::script::analyzer::operation::core (mu::script::context & context_a, boost::shared_ptr <mu::script::extensions::node> extensions, boost::shared_ptr <mu::io::ast::cluster> ast)
{
	boost::shared_ptr <mu::script::cluster::node> result;
	mu::io::analyzer::analyzer analyzer (boost::bind (&mu::script::analyzer::operation::build, this, &result, _1), context_a.errors, extensions->extensions);
	for (auto i (ast->expressions.begin ()), j (ast->expressions.end ()); i != j; ++i)
	{
		analyzer.input (*i);
	}
	mu::io::debugging::context context;
	if (ast->expressions.size () > 0)
	{
		auto last (ast->expressions [ast->expressions.size () - 1]);
		context = mu::io::debugging::context (last->context.last, last->context.last);
	}
	analyzer.input (boost::make_shared <mu::io::ast::end> (context));
	return result;
}

void mu::script::analyzer::operation::build (boost::shared_ptr <mu::script::cluster::node> * result_a, boost::shared_ptr <mu::core::cluster> cluster_a)
{
	mu::script_io::cluster cluster (cluster_a);
	*result_a = cluster.result;
}