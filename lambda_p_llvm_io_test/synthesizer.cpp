#include "synthesizer.h"

#include <lambda_p_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p_io/analyzer/extensions/extensions.h>
#include <lambda_p/routine.h>
#include <lambda_p_llvm_io/synthesizer.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p_llvm/function_pointer/node.h>
#include <lambda_p_io/analyzer/extensions/global.h>
#include <lambda_p_llvm/execution_engine/create_jit.h>
#include <lambda_p_llvm/execution_engine/run_function.h>
#include <lambda_p_llvm/execution_engine/generic_value/node.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/identity/operation.h>
#include <lambda_p_script_io/builder.h>

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
#include <llvm/Operator.h>

#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

void lambda_p_llvm_io_test::synthesizer::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void lambda_p_llvm_io_test::synthesizer::run_1 ()
{
	lambda_p_io::builder builder;
	llvm::LLVMContext context;
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (""), context)));
	auto fun (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage));
	auto function (boost::make_shared <lambda_p_llvm::function_pointer::node> (fun, false));
	auto block (llvm::BasicBlock::Create (context));
	fun->getBasicBlockList ().push_back (block);
	auto ret (llvm::ReturnInst::Create (context));
	block->getInstList ().push_back (ret);
	module->module->getFunctionList ().push_back (fun);
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
	llvm::PassManager PM;
	std::string text;
	llvm::raw_string_ostream stream (text);
	PM.add (llvm::createPrintModulePass (&stream));
	PM.run (*module->module);
	std::string analysis_errors;
	auto error (llvm::verifyModule (*module->module, llvm::VerifierFailureAction::ReturnStatusAction, &analysis_errors));
	assert (!error);
	assert (values.size () == 1);
	auto f1 (boost::dynamic_pointer_cast <lambda_p_llvm::function_pointer::node> (values [0]));
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
	auto fun (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt32Ty (context), false), llvm::GlobalValue::ExternalLinkage));
	auto function (boost::make_shared <lambda_p_llvm::function_pointer::node> (fun, false));
	auto block (llvm::BasicBlock::Create (context));
	fun->getBasicBlockList ().push_back (block);
	auto ret (llvm::ReturnInst::Create (context, llvm::ConstantInt::getIntegerValue (llvm::Type::getInt32Ty (context), llvm::APInt (32, 42))));
	block->getInstList ().push_back (ret);
	module->module->getFunctionList ().push_back (fun);
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
	llvm::PassManager PM;
	std::string text;
	llvm::raw_string_ostream stream (text);
	PM.add (llvm::createPrintModulePass (&stream));
	PM.run (*module->module);
	std::string analysis_errors;
	auto error (llvm::verifyModule (*module->module, llvm::VerifierFailureAction::ReturnStatusAction, &analysis_errors));
	assert (!error);
	assert (values.size () == 1);
	auto f1 (boost::dynamic_pointer_cast <lambda_p_llvm::function_pointer::node> (values [0]));
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
	auto fun (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt32Ty (context), arg_types, false), llvm::GlobalValue::ExternalLinkage));
	auto function (boost::make_shared <lambda_p_llvm::function_pointer::node> (fun, false));
	auto block (llvm::BasicBlock::Create (context));
	fun->getBasicBlockList ().push_back (block);
	llvm::Argument * arg (fun->arg_begin ());
	auto ret (llvm::ReturnInst::Create (context, arg));
	block->getInstList ().push_back (ret);
	module->module->getFunctionList ().push_back (fun);
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
	auto f1 (boost::dynamic_pointer_cast <lambda_p_llvm::function_pointer::node> (values [0]));
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

void lambda_p_llvm_io_test::synthesizer::run_4 ()
{
	lambda_p_io::builder builder;
	llvm::LLVMContext context;
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (""), context)));
	std::vector <llvm::Type *> res_types;
	res_types.push_back (llvm::Type::getInt32Ty (context));
	res_types.push_back (llvm::Type::getInt32Ty (context));
	auto res_type (llvm::StructType::create (context, res_types));
	auto fun (llvm::Function::Create (llvm::FunctionType::get (res_type, false), llvm::GlobalValue::ExternalLinkage));
	auto function (boost::make_shared <lambda_p_llvm::function_pointer::node> (fun, true));
	auto block (llvm::BasicBlock::Create (context));
	fun->getBasicBlockList ().push_back (block);
	std::vector <llvm::Constant *> result_values;
	result_values.push_back (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 0x33333333)));
	result_values.push_back (llvm::ConstantInt::get (llvm::Type::getInt32Ty (context), llvm::APInt (32, 0xcccccccc)));
	auto ret (llvm::ReturnInst::Create (context, llvm::ConstantStruct::get (res_type, result_values)));
	block->getInstList ().push_back (ret);
	module->module->getFunctionList ().push_back (fun);
	auto fun_1 (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getInt32Ty (context), res_types, false), llvm::GlobalValue::ExternalLinkage));
	auto fun1 (boost::make_shared <lambda_p_llvm::function_pointer::node> (fun_1, false));
	auto block2 (llvm::BasicBlock::Create (context));
	fun_1->getBasicBlockList ().push_back (block2);
	auto args (fun_1->arg_begin ());
	llvm::Value * arg1 (args);
	++args;
	llvm::Value * arg2 (args);
	auto add (llvm::BinaryOperator::CreateAdd (arg1, arg2));
	block2->getInstList ().push_back (add);
	auto ret2 (llvm::ReturnInst::Create (context, add));
	block2->getInstList ().push_back (ret2);
	module->module->getFunctionList ().push_back (fun_1);
	builder.analyzer.extensions->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"multi"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (function)));
	builder.analyzer.extensions->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"add"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (fun1)));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	lambda_p_llvm_io::synthesizer synthesizer;
	source (L"[add [multi]]");
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (routine);
	arguments.push_back (module);
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
	auto f1 (boost::dynamic_pointer_cast <lambda_p_llvm::function_pointer::node> (values [0]));
	assert (f1.get () != nullptr);
	assert (f1->multiple_return == false);
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
	auto r (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine::generic_value::node> (v2 [0]));
	assert (r.get () != nullptr);
	assert (r->value.IntVal.getLimitedValue () == 0xffffffff);
}

void lambda_p_llvm_io_test::synthesizer::run_5 ()
{
	lambda_p_io::builder builder;
	llvm::LLVMContext context;
	auto module (boost::make_shared <lambda_p_llvm::module::node> (new llvm::Module (llvm::StringRef (""), context)));
	auto fun (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context), false), llvm::GlobalValue::ExternalLinkage));
	auto function (boost::make_shared <lambda_p_llvm::function_pointer::node> (fun, false));
	auto block (llvm::BasicBlock::Create (context));
	fun->getBasicBlockList ().push_back (block);
	auto ret (llvm::ReturnInst::Create (context));
	block->getInstList ().push_back (ret);
	module->module->getFunctionList ().push_back (fun);
	builder.analyzer.extensions->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"noop"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (function)));
	builder.analyzer.extensions->extensions_m.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L".id"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::identity::operation> ())));
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	lambda_p_llvm_io::synthesizer synthesizer;
	source (L"[[.id noop; a]a]");
	auto routine (builder.routines [0]);
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	arguments.push_back (routine);
	arguments.push_back (module);
	std::vector <boost::shared_ptr <lambda_p::node>> values;
	synthesizer.perform (builder.errors, arguments, values);
	assert (builder.errors->errors.empty ());
	llvm::PassManager PM;
	std::string text;
	llvm::raw_string_ostream stream (text);
	PM.add (llvm::createPrintModulePass (&stream));
	PM.run (*module->module);
	std::string analysis_errors;
	auto error (llvm::verifyModule (*module->module, llvm::VerifierFailureAction::ReturnStatusAction, &analysis_errors));
	assert (!error);
	assert (values.size () == 1);
	auto f1 (boost::dynamic_pointer_cast <lambda_p_llvm::function_pointer::node> (values [0]));
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