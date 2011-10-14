#include "function_binder_test.h"

#include <lambda_p_llvm/function_binder.h>
#include <lambda_p/routine_builder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/fo_value.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>

void lambda_p_test::function_binder_test::run ()
{
	::lambda_p::routine_builder builder;
	builder (L"op one = result; op result = one; #;");
	::lambda_p::core::statement * statement (builder.routines.routines->operator[] (0)->statements [0]);
	::llvm::LLVMContext llvm_context;
	::llvm::Module * module (new ::llvm::Module (::llvm::StringRef ("test"), llvm_context));
	::std::vector < ::llvm::Type const *> a1;
	a1.push_back (::llvm::Type::getInt16Ty (llvm_context));
	::llvm::Function * target (::llvm::Function::Create (::llvm::FunctionType::get (::llvm::Type::getInt16Ty (llvm_context), a1, false), ::llvm::GlobalValue::ExternalLinkage, ::llvm::Twine ("llvm.bswap.i16")));
	module->getFunctionList ().push_back (target);
	::llvm::Function * function (::llvm::Function::Create (::llvm::FunctionType::get (::llvm::Type::getVoidTy (llvm_context), false), ::llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (function);
	::llvm::BasicBlock * block (::llvm::BasicBlock::Create (llvm_context));
	function->getBasicBlockList ().push_back (block);
	::lambda_p_llvm::generation_context context (llvm_context, module, block);
	::lambda_p_llvm::function_binder binder (context, target);
	::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > problems;
	::lambda_p::binder::routine_instances & instances (builder.routines.routines->operator[] (0)->instances);
	instances [statement->association->parameters [0]] = ::boost::shared_ptr < ::lambda_p_llvm::fo_value> (new ::lambda_p_llvm::fo_value (::llvm::ConstantInt::get (::llvm::Type::getInt16Ty (llvm_context), 0xffcc)));
	binder.bind (statement, instances, problems);
	assert (instances [statement->association->results [0]].get () != NULL);
	assert (block->getInstList ().size () == 1);
}