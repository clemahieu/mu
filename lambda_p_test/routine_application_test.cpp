#include "routine_application_test.h"

#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/routine_application.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/literal_value.h>
#include <lambda_p/routine_from_stream.h>
#include <lambda_p_llvm/generator.h>
#include <lambda_p/binder/routine.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p/binder/bind_procedure.h>

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
	::lambda_p::routine_from_stream routine;
	routine (L"add a b c = result; add res = a b; add result = res c; #;");
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
	::lambda_p::routine_from_stream enclosing;
	enclosing (L"generator routine add result_type p1_type p2_type p3_type = func; generator func = routine result_type add p1_type p2_type p3_type; #;");
	::lambda_p::binder::routine_instances & instances (enclosing.routines.routines->operator[] (0)->instances);
	::boost::shared_ptr < ::lambda_p_llvm::generator> generator (new ::lambda_p_llvm::generator (context));
	instances [0] = generator;
	::boost::shared_ptr < ::lambda_p::binder::routine> routine_value (new ::lambda_p::binder::routine (::boost::shared_ptr < ::lambda_p::core::routine> (routine.routines.routines->operator[] (0))));
	instances [1] = routine_value;
	::boost::shared_ptr < ::lambda_p_llvm::literal_value> add_value (new ::lambda_p_llvm::literal_value (add_function));
	instances [2] = add_value;
	::boost::shared_ptr < ::lambda_p_llvm::type> type_value (new ::lambda_p_llvm::type (::llvm::Type::getInt64Ty (llvm_context)));
	instances [3] = type_value;
	instances [4] = type_value;
	instances [5] = type_value;
	instances [6] = type_value;
	::lambda_p::binder::bind_procedure procedure (::boost::shared_ptr < ::lambda_p::core::routine> (enclosing.routines.routines->operator[] (0)));
	::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > problems;
	procedure (problems);
	assert (problems.size () == 0);
}