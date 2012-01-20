#include "synthesizer.h"

#include <lambda_p_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>
#include <lambda_p/routine.h>
#include <lambda_p_llvm_io/synthesizer.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/function/node.h>
#include <lambda_p_io/analyzer/extensions/global.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void lambda_p_llvm_io_test::synthesizer::run ()
{
	run_1 ();
}

void lambda_p_llvm_io_test::synthesizer::run_1 ()
{
	lambda_p_io::builder builder;
	llvm::LLVMContext context;
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (""), context)));
	auto function (boost::make_shared <lambda_p_llvm::function::node> (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage), false));
	module->module->getFunctionList ().push_back (function->function ());
	builder.analyzer.extensions->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"noop"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (function)));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	lambda_p_llvm_io::synthesizer synthesizer;
	source (L"[noop]");
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (routine);
	arguments.push_back (module);
	std::vector <boost::shared_ptr <lambda_p::node>> values;
	synthesizer.perform (builder.errors, arguments, values);
	assert (values.size () == 1);
	auto function (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (values [0]));
	assert (function.get () != nullptr);
	assert (function->multiple_return = false);
}