#include "synthesizer.h"

#include <lambda_p_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>
#include <lambda_p/routine.h>
#include <lambda_p_llvm_io/synthesizer.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/function/node.h>
#include <lambda_p_io/analyzer/extensions/global.h>
#include <lambda_p_llvm/execution_engine/create_jit.h>
#include <lambda_p_llvm/execution_engine/run_function.h>
#include <lambda_p_llvm/execution_engine/generic_value/node.h>
#include <lambda_p_llvm/type/node.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Instructions.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Constants.h>
#include <llvm/PassManager.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/raw_ostream.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void lambda_p_llvm_io_test::synthesizer::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_llvm_io_test::synthesizer::run_1 ()
{
	lambda_p_io::builder builder;
	llvm::LLVMContext context;
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (""), context)));
	auto function (boost::make_shared <lambda_p_llvm::function::node> (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage), false));
	auto block (llvm::BasicBlock::Create (context));
	function->function ()->getBasicBlockList ().push_back (block);
	auto ret (llvm::ReturnInst::Create (context));
	block->getInstList ().push_back (ret);
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
	std::string analysis_errors;
	auto error (llvm::verifyModule (*module->module, llvm::VerifierFailureAction::ReturnStatusAction, &analysis_errors));
	assert (!error);
	assert (values.size () == 1);
	auto f1 (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (values [0]));
	assert (f1.get () != nullptr);
	lambda_p_llvm::execution_engine::create_jit create_jit;
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	std::vector <boost::shared_ptr <lambda_p::node>> v1;
	a1.push_back (module);
	create_jit (builder.errors, a1, v1);
	assert (builder.errors->errors.empty ());
	assert (v1.size () == 1);
	auto engine (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine::node> (v1 [0]));
	assert (engine.get () != nullptr);
	lambda_p_llvm::execution_engine::run_function run_function;
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> v2;
	a2.push_back (engine);
	a2.push_back (f1);
	run_function.perform (builder.errors, a2, v2);
	assert (v2.size () == 1);
}

void lambda_p_llvm_io_test::synthesizer::run_2 ()
{
	lambda_p_io::builder builder;
	llvm::LLVMContext context;
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (""), context)));
	auto function (boost::make_shared <lambda_p_llvm::function::node> (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt32Ty (context), false), llvm::GlobalValue::ExternalLinkage), false));
	auto block (llvm::BasicBlock::Create (context));
	function->function ()->getBasicBlockList ().push_back (block);
	auto ret (llvm::ReturnInst::Create (context, llvm::ConstantInt::getIntegerValue (llvm::Type::getInt32Ty (context), llvm::APInt (32, 42))));
	block->getInstList ().push_back (ret);
	module->module->getFunctionList ().push_back (function->function ());
	builder.analyzer.extensions->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"val"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (function)));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	lambda_p_llvm_io::synthesizer synthesizer;
	source (L"[val]");
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (routine);
	arguments.push_back (module);
	std::vector <boost::shared_ptr <lambda_p::node>> values;
	synthesizer.perform (builder.errors, arguments, values);
	std::string analysis_errors;
	auto error (llvm::verifyModule (*module->module, llvm::VerifierFailureAction::ReturnStatusAction, &analysis_errors));
	assert (!error);
	assert (values.size () == 1);
	auto f1 (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (values [0]));
	assert (f1.get () != nullptr);
	lambda_p_llvm::execution_engine::create_jit create_jit;
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	std::vector <boost::shared_ptr <lambda_p::node>> v1;
	a1.push_back (module);
	create_jit (builder.errors, a1, v1);
	assert (builder.errors->errors.empty ());
	assert (v1.size () == 1);
	auto engine (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine::node> (v1 [0]));
	assert (engine.get () != nullptr);
	lambda_p_llvm::execution_engine::run_function run_function;
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> v2;
	a2.push_back (engine);
	a2.push_back (f1);
	run_function.perform (builder.errors, a2, v2);
	assert (v2.size () == 1);
	auto res (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine::generic_value::node> (v2 [0]));
	assert (res.get () != nullptr);
	assert (res->value.IntVal == 42);
}

void lambda_p_llvm_io_test::synthesizer::run_3 ()
{
	lambda_p_io::builder builder;
	llvm::LLVMContext context;
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (""), context)));
	std::vector <llvm::Type *> arg_types;
	arg_types.push_back (llvm::Type::getInt32Ty (context));
	auto function (boost::make_shared <lambda_p_llvm::function::node> (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt32Ty (context), arg_types, false), llvm::GlobalValue::ExternalLinkage), false));
	auto block (llvm::BasicBlock::Create (context));
	function->function ()->getBasicBlockList ().push_back (block);
	llvm::Argument * arg (function->function ()->arg_begin ());
	auto ret (llvm::ReturnInst::Create (context, arg));
	block->getInstList ().push_back (ret);
	module->module->getFunctionList ().push_back (function->function ());
	builder.analyzer.extensions->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"val"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (function)));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	lambda_p_llvm_io::synthesizer synthesizer;
	source (L"[val :~]");
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (routine);
	arguments.push_back (module);
	arguments.push_back (boost::make_shared <lambda_p_llvm::type::node> (llvm::Type::getInt32Ty (context)));
	std::vector <boost::shared_ptr <lambda_p::node>> values;
	synthesizer.perform (builder.errors, arguments, values);
	llvm::PassManager PM;
	std::string text;
	llvm::raw_string_ostream stream (text);
	PM.add (llvm::createPrintModulePass (&stream));
	PM.run (*module->module);
	std::string analysis_errors;
	auto error (llvm::verifyModule (*module->module, llvm::VerifierFailureAction::ReturnStatusAction, &analysis_errors));
	assert (!error);
	assert (values.size () == 1);
	auto f1 (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (values [0]));
	assert (f1.get () != nullptr);
	lambda_p_llvm::execution_engine::create_jit create_jit;
	std::vector <boost::shared_ptr <lambda_p::node>> a1;
	std::vector <boost::shared_ptr <lambda_p::node>> v1;
	a1.push_back (module);
	create_jit (builder.errors, a1, v1);
	assert (builder.errors->errors.empty ());
	assert (v1.size () == 1);
	auto engine (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine::node> (v1 [0]));
	assert (engine.get () != nullptr);
	lambda_p_llvm::execution_engine::run_function run_function;
	std::vector <boost::shared_ptr <lambda_p::node>> a2;
	std::vector <boost::shared_ptr <lambda_p::node>> v2;
	a2.push_back (engine);
	a2.push_back (f1);
	llvm::GenericValue val;
	val.IntVal = llvm::APInt (32, 42);
	a2.push_back (boost::make_shared <lambda_p_llvm::execution_engine::generic_value::node> (val));
	run_function.perform (builder.errors, a2, v2);
	assert (v2.size () == 1);
	auto res (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine::generic_value::node> (v2 [0]));
	assert (res.get () != nullptr);
	assert (res->value.IntVal == 42);
}