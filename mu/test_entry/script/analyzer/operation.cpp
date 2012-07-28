#include <mu/core/errors/error_list.h>
#include <mu/script/analyzer/operation.h>
#include <mu/io/ast/cluster.h>
#include <mu/script/extensions/node.h>
#include <mu/script/context.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, analyzer_operation1)
{
	mu::core::errors::error_list errors;
	mu::script::context ctx (errors);
	mu::script::analyzer::operation analyzer;
	auto cluster (analyzer.core (ctx, new (GC) mu::script::extensions::node, new (GC) mu::io::ast::cluster));
	EXPECT_TRUE (cluster != nullptr);
}