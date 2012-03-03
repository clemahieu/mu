#include <mu/llvm_test/constant_string.extension.h>

#include <mu/core/errors.error_list.h>
#include <mu/io/builder.h>
#include <mu/io/source.h>
#include <mu/llvm_/constant_string.extension.h>
#include <mu/io/ast.cluster.h>
#include <mu/io/ast.expression.h>
#include <mu/io/analyzer.expression.h>
#include <mu/io/analyzer.routine.h>
#include <mu/io/analyzer.analyzer.h>
#include <mu/core/expression.h>
#include <mu/llvm_/context.node.h>
#include <mu/llvm_/module.node.h>
#include <mu/io/analyzer.extensions.extensions.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

void mu::llvm_test::constant_string::extension::run ()
{
	run_1 ();
}

void mu::llvm_test::constant_string::extension::run_1 ()
{
	mu::io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[` test_string]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->expressions.size () == 1);
	auto expression (cluster->expressions [0]);
	assert (expression->values.size () == 2);
	mu::io::analyzer::analyzer analyzer (boost::bind (&mu::llvm_test::constant_string::extension::junk, this, _1), builder.errors);
	mu::io::analyzer::routine rout (analyzer, expression.get ());
	auto self (boost::make_shared <mu::core::expression> (mu::core::context ()));
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <mu::llvm_::context::node> (&context));
	auto module (boost::make_shared <mu::llvm_::module::node> (new llvm::Module (llvm::StringRef (""), context)));
	analyzer.extensions->extensions_m [L"`"] = boost::make_shared <mu::llvm_::constant_string::extension> (ctx, module);
	mu::io::analyzer::expression exp (rout, expression.get (), self);
	assert (builder.errors->errors.empty ());
}

void mu::llvm_test::constant_string::extension::junk (boost::shared_ptr <mu::core::cluster> cluster_a)
{

}
