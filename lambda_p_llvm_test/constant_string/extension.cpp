#include "extension.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_llvm/constant_string/extension.h>
#include <lambda_p_io/ast/cluster.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/analyzer/expression.h>
#include <lambda_p_io/analyzer/routine.h>
#include <lambda_p_io/analyzer/analyzer.h>
#include <lambda_p/expression.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

void lambda_p_llvm_test::constant_string::extension::run ()
{
	run_1 ();
}

void lambda_p_llvm_test::constant_string::extension::run_1 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[` test_string]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->expressions.size () == 1);
	auto expression (cluster->expressions [0]);
	assert (expression->values.size () == 2);
	lambda_p_io::analyzer::analyzer analyzer (boost::bind (&lambda_p_llvm_test::constant_string::extension::junk, this, _1), builder.errors);
	lambda_p_io::analyzer::routine rout (analyzer, expression.get ());
	auto self (boost::make_shared <lambda_p::expression> (lambda_p::context ()));
	llvm::LLVMContext context;
	auto ctx (boost::make_shared <lambda_p_llvm::context::node> (&context));
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (""), context)));
	analyzer.extensions->extensions_m [L"`"] = boost::make_shared <lambda_p_llvm::constant_string::extension> (ctx, module);
	lambda_p_io::analyzer::expression exp (rout, expression.get (), self);
	assert (builder.errors->errors.empty ());
}

void lambda_p_llvm_test::constant_string::extension::junk (boost::shared_ptr <lambda_p::cluster> cluster_a)
{

}