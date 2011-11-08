#include "generator_test.h"

#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p/builder.h>
#include <lambda_p_llvm/generator.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p_kernel/apply.h>

#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/Operator.h>

void lambda_p_test::generator_test::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::generator_test::run_1 ()
{
	lambda_p::builder inner;
	inner (L"value; value; :;");
	boost::shared_ptr <lambda_p::binder::list> inner_list (new lambda_p::binder::list);
	llvm::LLVMContext context;
	inner_list->operator[] (0) = boost::shared_ptr <lambda_p_llvm::type> (new lambda_p_llvm::type (llvm::Type::getInt16Ty (context)));
	lambda_p::builder outer;
	outer (L"func; generator module routine list; generator module routine list; func; :;");
	boost::shared_ptr <lambda_p::binder::list> outer_list (new lambda_p::binder::list);
	outer_list->operator[] (0) = boost::shared_ptr <lambda_p_llvm::generator> (new lambda_p_llvm::generator);
	outer_list->operator[] (1) = boost::shared_ptr <lambda_p_llvm::module> (new lambda_p_llvm::module (new llvm::Module (llvm::StringRef ("test"), context)));
	outer_list->operator[] (2) = inner.routines.routines->operator[] (0);
	outer_list->operator[] (3) = inner_list;
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	lambda_p::binder::list declarations;
	apply.core (outer.routines.routines->operator[] (0), *outer_list, problems, declarations);
	assert (problems.errors.empty ());
	assert (declarations.nodes.size () == 1);
	boost::shared_ptr <lambda_p_llvm::value> value (boost::dynamic_pointer_cast <lambda_p_llvm::value> (declarations [0]));
	assert (value.get () != nullptr);
	auto function (llvm::dyn_cast <llvm::Function> (value->value_m));
	assert (function != nullptr);
	assert (function->getReturnType () == llvm::Type::getInt16Ty (context));
	assert (function->getBasicBlockList ().size () == 1);
	assert (function->getBasicBlockList ().begin ()->getInstList ().size () == 1);
	llvm::Instruction * inst (function->getBasicBlockList ().begin ()->getInstList ().begin ());
	assert (inst != nullptr);
	llvm::ReturnInst * return_inst (llvm::dyn_cast <llvm::ReturnInst> (inst));
	assert (return_inst != nullptr);
}

void lambda_p_test::generator_test::run_2 ()
{
	lambda_p::builder inner;
	inner (L"ret; value; value; ret; :;");
	boost::shared_ptr <lambda_p::binder::list> inner_list (new lambda_p::binder::list);
	llvm::LLVMContext context;
	auto module (new llvm::Module (llvm::StringRef ("test"), context));
	auto called_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getDoubleTy (context), false), llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (called_function);
	inner_list->operator[] (0) = boost::shared_ptr <lambda_p_llvm::value> (new lambda_p_llvm::value (called_function));
	lambda_p::builder outer;
	outer (L"func; generator module routine list; generator module routine list; func; :;");
	boost::shared_ptr <lambda_p::binder::list> outer_list (new lambda_p::binder::list);
	outer_list->operator[] (0) = boost::shared_ptr <lambda_p_llvm::generator> (new lambda_p_llvm::generator);
	outer_list->operator[] (1) = boost::shared_ptr <lambda_p_llvm::module> (new lambda_p_llvm::module (module));
	outer_list->operator[] (2) = inner.routines.routines->operator[] (0);
	outer_list->operator[] (3) = inner_list;
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	lambda_p::binder::list declarations;
	apply.core (outer.routines.routines->operator[] (0), *outer_list, problems, declarations);
	assert (problems.errors.empty ());
	assert (declarations.nodes.size () == 1);
	boost::shared_ptr <lambda_p_llvm::value> value (boost::dynamic_pointer_cast <lambda_p_llvm::value> (declarations [0]));
	assert (value.get () != nullptr);
	auto function (llvm::dyn_cast <llvm::Function> (value->value_m));
	assert (function != nullptr);
	assert (function->getReturnType () == llvm::Type::getDoubleTy (context));
	assert (function->getBasicBlockList ().size () == 1);
	assert (function->getBasicBlockList ().begin ()->getInstList ().size () == 2);
	auto list (function->getBasicBlockList ().begin ()->getInstList ().begin ());
	llvm::Instruction * inst (list);
	assert (inst != nullptr);
	llvm::CallInst * call_inst (llvm::dyn_cast <llvm::CallInst> (inst));
	assert (call_inst != nullptr);
	++list;
	llvm::Instruction * inst2 (list);
	assert (inst2 != nullptr);
	llvm::ReturnInst * return_inst (llvm::dyn_cast <llvm::ReturnInst> (inst2));
	assert (return_inst != nullptr);
}