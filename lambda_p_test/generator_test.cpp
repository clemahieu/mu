#include "generator_test.h"

#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p/routine_builder.h>
#include <lambda_p_llvm/generator.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p_kernel/list_binder.h>

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
}

void lambda_p_test::generator_test::run_1 ()
{
	lambda_p::routine_builder routine;
	routine (L"fma a b c d e = result; fma res = a b c; fma result = res d e; #;");
	llvm::LLVMContext llvm_context;
	llvm::StringRef name ("test");
	llvm::Module * module (new llvm::Module (name, llvm_context));
	std::vector < llvm::Type const *> fma_parameters;
	fma_parameters.push_back (llvm::Type::getDoubleTy (llvm_context));
	fma_parameters.push_back (llvm::Type::getDoubleTy (llvm_context));
	fma_parameters.push_back (llvm::Type::getDoubleTy (llvm_context));
	llvm::Function * fma (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getDoubleTy (llvm_context), fma_parameters, false), llvm::GlobalValue::ExternalLinkage, llvm::Twine ("llvm.fma.f64")));
	module->getFunctionList ().push_back (fma);
	llvm::Function * start (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (llvm_context), false), llvm::GlobalValue::ExternalLinkage));
	module->getFunctionList ().push_back (start);
	llvm::BasicBlock * block (llvm::BasicBlock::Create (llvm_context));
	start->getBasicBlockList ().push_back (block);
	lambda_p_llvm::generation_context context (llvm_context, module, block);
	lambda_p::routine_builder enclosing;
	enclosing (L"generator routine fma result_type p1_type p2_type p3_type p4_type p5_type group = func; group arguments = fma p1_type p2_type p3_type p4_type p5_type; generator func = routine result_type arguments; #;");
	lambda_p::binder::routine_instances & instances (enclosing.routines.routines->operator[] (0)->instances);
	boost::shared_ptr < lambda_p_llvm::generator> generator (new lambda_p_llvm::generator (context));
	instances [0] = generator;
	boost::shared_ptr < lambda_p_kernel::routine> routine_value (new lambda_p_kernel::routine (boost::shared_ptr < lambda_p::core::routine> (routine.routines.routines->operator[] (0))));
	instances [1] = routine_value;
	boost::shared_ptr < lambda_p_llvm::fo_value> fma_value (new lambda_p_llvm::fo_value (fma));
	instances [2] = fma_value;
	boost::shared_ptr < lambda_p_llvm::type> type_value (new lambda_p_llvm::type (llvm::Type::getDoubleTy (llvm_context)));
	instances [3] = type_value;
	instances [4] = type_value;
	instances [5] = type_value;
	instances [6] = type_value;
	instances [7] = type_value;
	instances [8] = type_value;
	boost::shared_ptr < lambda_p_kernel::list_binder> group (new lambda_p_kernel::list_binder);
	instances [9] = group;
	lambda_p_kernel::bind_procedure procedure (boost::shared_ptr < lambda_p::core::routine> (enclosing.routines.routines->operator[] (0)));
	std::vector < boost::shared_ptr < lambda_p::errors::error> > problems;
	procedure (problems);
	assert (problems.size () == 0);
	boost::shared_ptr < lambda_p::binder::instance> final (instances [enclosing.routines.routines->operator[] (0)->surface->parameters [0]]);
	assert (final.get () != NULL);
}