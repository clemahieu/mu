#include <mu/core/errors/error_list.h>
#include <mu/io/ast/builder.h>
#include <mu/io/source.h>
#include <mu/llvm_/constant_string/extension.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/expression.h>
#include <mu/io/analyzer/expression.h>
#include <mu/io/analyzer/routine.h>
#include <mu/io/analyzer/analyzer.h>
#include <mu/core/expression.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/io/analyzer/extensions/extensions.h>

#include <boost/bind.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

static void junk (mu::core::cluster * cluster_a)
{

}

TEST (llvm_test, constant_string_extension1)
{
	mu::io::ast::builder builder;
	mu::io::process (builder, U"[` test_string]");
	EXPECT_EQ (builder.errors->errors.empty (), true);
	auto cluster (builder.cluster);
	EXPECT_EQ (cluster->expressions.size (), 1);
	auto expression (cluster->expressions [0]);
	EXPECT_EQ (expression->values.size (), 2);
	mu::io::analyzer::analyzer analyzer (boost::bind (&junk, _1), builder.errors);
	mu::io::analyzer::routine rout (analyzer, expression);
	auto self (new (GC) mu::core::expression);
	llvm::LLVMContext context;
	auto ctx (new (GC) mu::llvm_::context::node (&context));
	auto module (new (GC) mu::llvm_::module::node (new llvm::Module (llvm::StringRef (""), context)));
	(*analyzer.extensions) (mu::string (U"`"), new (GC) mu::llvm_::constant_string::extension (module));
	mu::io::analyzer::expression exp (rout, expression, self);
	EXPECT_EQ (builder.errors->errors.empty (), true);
}