#include "routine_application_test.h"

#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/routine_application.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/literal_value.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Operator.h>

void lambda_p_test::routine_application_test::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::routine_application_test::run_1 ()
{
	::lambda_p::core::routine routine;
	::lambda_p_llvm::routine_application application (&routine);
	::llvm::LLVMContext llvm_context;
	::llvm::StringRef name ("test");
	::llvm::Module * module (new ::llvm::Module (name, llvm_context));
	::llvm::Function * start (::llvm::Function::Create (::llvm::FunctionType::get (::llvm::Type::getVoidTy (llvm_context), false), ::llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (start);
	::llvm::BasicBlock * block (::llvm::BasicBlock::Create (llvm_context));
	start->getBasicBlockList ().push_back (block);
	::lambda_p_llvm::generation_context context (llvm_context, module, block);
	::std::vector < ::lambda_p::errors::error *> problems;
	::llvm::Function * function (application.generate (context, ::std::vector < ::llvm::Type const *> (), ::std::vector < ::llvm::Type const *> (), problems));
	assert (problems.size () == 0);
	assert (function != NULL);
}

void lambda_p_test::routine_application_test::run_2 ()
{
	::lambda_p::core::routine routine;
	size_t add (routine.add_declaration ());
	size_t a (routine.add_declaration ());
	size_t b (routine.add_declaration ());
	size_t c (routine.add_declaration ());
	routine.surface->results.push_back (add);
	routine.surface->results.push_back (a);
	routine.surface->results.push_back (b);
	::llvm::LLVMContext llvm_context;
	::llvm::StringRef name ("test");
	::llvm::Module * module (new ::llvm::Module (name, llvm_context));
	::std::vector < ::llvm::Type const *> add_parameters;
	add_parameters.push_back (::llvm::Type::getInt64Ty (llvm_context));
	add_parameters.push_back (::llvm::Type::getInt64Ty (llvm_context));
	::llvm::Function * add_function (::llvm::Function::Create (::llvm::FunctionType::get (::llvm::Type::getInt64Ty (llvm_context), add_parameters, false), ::llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (add_function);
	::llvm::BasicBlock * add_block (::llvm::BasicBlock::Create (llvm_context));
	add_function->getBasicBlockList ().push_back (add_block);
	::llvm::Function::arg_iterator i (add_function->arg_begin ());
	::llvm::Value * arg1 (&(*i));
	++i;
	::llvm::Value * arg2 (&(*i));
	::llvm::BinaryOperator * add_operator (::llvm::BinaryOperator::CreateAdd (arg1, arg2));
	add_block->getInstList ().push_back (add_operator);
	add_block->getInstList ().push_back (::llvm::ReturnInst::Create (llvm_context, add_operator));
	::llvm::Function * start (::llvm::Function::Create (::llvm::FunctionType::get (::llvm::Type::getVoidTy (llvm_context), false), ::llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (start);
	::llvm::BasicBlock * block (::llvm::BasicBlock::Create (llvm_context));
	start->getBasicBlockList ().push_back (block);
	::lambda_p_llvm::generation_context context (llvm_context, module, block);
	::lambda_p_llvm::routine_application application (&routine);
	::std::vector < ::lambda_p_llvm::value *> arguments;
	arguments.push_back (new ::lambda_p_llvm::literal_value (add_function));
	application.apply (arguments);
	assert (application.indirection.size () == 2);
	assert (application.indirection [0] == 1);
	assert (application.indirection [1] == 2);
	::std::vector < ::lambda_p::errors::error *> problems;
	::std::vector < ::llvm::Type const *> function_parameters;
	function_parameters.push_back (::llvm::Type::getInt64Ty (llvm_context));
	function_parameters.push_back (::llvm::Type::getInt64Ty (llvm_context));
	function_parameters.push_back (::llvm::Type::getInt64Ty (llvm_context));
	::llvm::Function * function (application.generate (context, function_parameters, ::std::vector < ::llvm::Type const *> (), problems));
	assert (problems.size () == 0);
	assert (function != NULL);
}