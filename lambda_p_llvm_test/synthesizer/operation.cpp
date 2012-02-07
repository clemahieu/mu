#include "operation.h"

#include <lambda_p_io/source.h>
#include <lambda_p_script_io/builder.h>
#include <lambda_p_llvm/synthesizer/operation.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_io/ast/cluster.h>

#include <boost/bind.hpp>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm_test::synthesizer::operation::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_llvm_test::synthesizer::operation::run_1 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[.id .ast []]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	builder.clusters [0]->routines [0]->perform (builder.errors, a1, r1);
	assert (r1.size () == 1);
	auto ast (boost::dynamic_pointer_cast <lambda_p_io::ast::cluster> (r1 [0]));
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (ast);
	a2.push_back (module);
	lambda_p_llvm::synthesizer::operation synthesizer;
	synthesizer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 0);
}

void lambda_p_llvm_test::synthesizer::operation::run_2 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[.id .ast [[function_type [{] [{]] []]]");
	source ();
	assert (builder.errors->errors.empty ());
	llvm::LLVMContext context_l;
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	std::vector <boost::shared_ptr <lambda_p::node>> r1;
	builder.clusters [0]->routines [0]->perform (builder.errors, a1, r1);
	assert (r1.size () == 1);
	auto ast (boost::dynamic_pointer_cast <lambda_p_io::ast::cluster> (r1 [0]));
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (), context_l)));	
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> r2;
	a2.push_back (ast);
	a2.push_back (module);
	lambda_p_llvm::synthesizer::operation synthesizer;
	synthesizer.perform (builder.errors, a2, r2);
	assert (builder.errors->errors.empty ());
	assert (module->module->getFunctionList ().size () == 1);
}