#include "operation.h"

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

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void mu::script::analyzer::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto extensions (boost::dynamic_pointer_cast <mu::script::extensions::node> (parameters [0]));
	auto ast (boost::dynamic_pointer_cast <mu::io::ast::cluster> (parameters [1]));
	if (extensions.get () != nullptr)
	{
		if (ast.get () != nullptr)
		{
			auto result (core (errors_a, extensions, ast));
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::script::analyzer::operation::count ()
{
	return 2;
}

boost::shared_ptr <mu::script::cluster::node> mu::script::analyzer::operation::core (boost::shared_ptr <mu::core::errors::error_target> errors_a, boost::shared_ptr <mu::script::extensions::node> extensions, boost::shared_ptr <mu::io::ast::cluster> ast)
{
	boost::shared_ptr <mu::script::cluster::node> result;
	mu::io::analyzer::analyzer analyzer (boost::bind (&mu::script::analyzer::operation::build, this, &result, _1), errors_a, extensions->extensions);
	for (auto i (ast->expressions.begin ()), j (ast->expressions.end ()); i != j; ++i)
	{
		analyzer.input (*i);
	}
	mu::core::context context;
	if (ast->expressions.size () > 0)
	{
		auto last (ast->expressions [ast->expressions.size () - 1]);
		context = mu::core::context (last->context.last, last->context.last);
	}
	analyzer.input (boost::make_shared <mu::io::ast::end> (context));
	return result;
}

void mu::script::analyzer::operation::build (boost::shared_ptr <mu::script::cluster::node> * result_a, boost::shared_ptr <mu::core::cluster> cluster_a)
{
	mu::script_io::cluster cluster (cluster_a);
	*result_a = cluster.result;
}