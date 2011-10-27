#include "noop_closure_test.h"

#include <lambda_p_llvm/noop_closure.h>
#include <lambda_p_llvm/noop_closure_binder.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p_kernel/single_bind_routine.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p_llvm/call_binder.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/routine_builder.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/Instructions.h>

void lambda_p_test::noop_closure_test::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::noop_closure_test::run_1 ()
{
	llvm::LLVMContext llvm_context;
	llvm::StringRef name ("test");
	llvm::Module * module (new llvm::Module (name, llvm_context));
	llvm::Function * start (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (llvm_context), false), llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (start);
	llvm::BasicBlock * block (llvm::BasicBlock::Create (llvm_context));
	start->getBasicBlockList ().push_back (block);
	lambda_p_llvm::generation_context context (llvm_context, module, block);
	llvm::Function * target (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (llvm_context), false), llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (target);
	std::vector < llvm::Value *> arguments;
	lambda_p_llvm::noop_closure closure (context, target, arguments);
	closure.operator() ();
	assert (block->getInstList ().size () == 1);
	assert (llvm::isa < llvm::CallInst> (*block->getInstList ().begin ()));
}

void lambda_p_test::noop_closure_test::run_2 ()
{
	llvm::LLVMContext llvm_context;
	llvm::StringRef name ("test");
	llvm::Module * module (new llvm::Module (name, llvm_context));
	llvm::Function * start (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (llvm_context), false), llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (start);
	llvm::BasicBlock * block (llvm::BasicBlock::Create (llvm_context));
	start->getBasicBlockList ().push_back (block);
	lambda_p_llvm::generation_context context (llvm_context, module, block);
	llvm::Function * target (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (llvm_context), false), llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (target);
	std::vector < llvm::Value *> arguments;
	boost::shared_ptr <lambda_p_llvm::noop_closure_binder> binder (new lambda_p_llvm::noop_closure_binder (context));
	boost::shared_ptr <lambda_p_llvm::fo_value> function (new lambda_p_llvm::fo_value (target));
	boost::shared_ptr <lambda_p_llvm::call_binder> call (new lambda_p_llvm::call_binder);
	boost::shared_ptr <lambda_p::binder::list_binder> list (new lambda_p::binder::list_binder);
	lambda_p::routine_builder builder;
	builder (L"; binder function call list; list ; args ; binder function args; closure; call closure;; :;");
	boost::shared_ptr <lambda_p::core::routine> routine (builder.routines.routines->operator[] (0));
	boost::shared_ptr <lambda_p::binder::routine_instances> instances (new lambda_p::binder::routine_instances);
	instances->operator[] (routine->surface->results [0]) = binder;
	instances->operator[] (routine->surface->results [1]) = function;
	instances->operator[] (routine->surface->results [2]) = call;
	instances->operator[] (routine->surface->results [3]) = list;
	boost::shared_ptr <lambda_p_kernel::routine> routine_instance (new lambda_p_kernel::routine (routine));
	lambda_p_kernel::single_bind_routine bind_action (routine_instance, instances);
	lambda_p::errors::error_list problems;
	bind_action (problems);
	assert (problems.errors.size () == 0);
	size_t count (block->getInstList ().size ());
	assert (count == 1);
	assert (llvm::isa < llvm::CallInst> (*block->getInstList ().begin ()));
}