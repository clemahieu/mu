#include <mu/core/errors/error_list.h>
#include <mu/script/analyzer/operation.h>
#include <mu/io/ast/cluster.h>
#include <mu/script/extensions/node.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

#include <gtest/gtest.h>

TEST (script_test, analyzer_operation1)
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context ctx (errors);
	mu::script::analyzer::operation analyzer;
	auto cluster (analyzer.core (ctx, boost::make_shared <mu::script::extensions::node> (), boost::make_shared <mu::io::ast::cluster> ()));
	EXPECT_NE (cluster.get (), nullptr);
}