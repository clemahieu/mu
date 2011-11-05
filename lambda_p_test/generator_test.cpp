#include "generator_test.h"

#include <lambda_p/core/routine.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p/builder.h>
#include <lambda_p_llvm/generator.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/errors/error_list.h>

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
	lambda_p::builder routine;
	routine (L"result; fma a b c d e; fma a b c; res; fma res d e; result; :;");
	llvm::LLVMContext llvm_context;
	llvm::StringRef name ("test");
	llvm::Module * module (new llvm::Module (name, llvm_context));
	std::vector <llvm::Type const *> fma_parameters;
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
	lambda_p::builder enclosing;
	enclosing (L"func; generator routine fma result_type p1_type p2_type p3_type p4_type p5_type group; group fma p1_type p2_type p3_type p4_type p5_type; arguments; generator routine result_type arguments; func; :;");
	lambda_p::binder::list nodes;
	boost::shared_ptr <lambda_p_llvm::generator> generator (new lambda_p_llvm::generator (context));
	nodes [0] = generator;
	boost::shared_ptr <lambda_p_kernel::routine> routine_value (new lambda_p_kernel::routine (boost::shared_ptr < lambda_p::core::routine> (routine.routines.routines->operator[] (0))));
	nodes [1] = routine_value;
	boost::shared_ptr <lambda_p_llvm::fo_value> fma_value (new lambda_p_llvm::fo_value (fma));
	nodes [2] = fma_value;
	boost::shared_ptr <lambda_p_llvm::type> type_value (new lambda_p_llvm::type (llvm::Type::getDoubleTy (llvm_context)));
	nodes [3] = type_value;
	nodes [4] = type_value;
	nodes [5] = type_value;
	nodes [6] = type_value;
	nodes [7] = type_value;
	nodes [8] = type_value;
	boost::shared_ptr <lambda_p::binder::list_binder> group (new lambda_p::binder::list_binder);
	nodes [9] = group;
	lambda_p_kernel::bind_procedure procedure (boost::shared_ptr <lambda_p::core::routine> (enclosing.routines.routines->operator[] (0)), nodes);
	lambda_p::errors::error_list problems;
	procedure (problems);
	assert (problems.errors.size () == 0);
	boost::shared_ptr <lambda_p::binder::node> final (nodes [enclosing.routines.routines->operator[] (0)->surface->references [0]]);
	assert (final.get () != nullptr);
}