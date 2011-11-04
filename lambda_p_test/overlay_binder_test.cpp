#include "overlay_binder_test.h"

#include <lambda_p_llvm/overlay_binder.h>
#include <lambda_p_llvm/execution_engine.h>
#include <lambda_p_llvm/module.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/builder.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_kernel/package.h>

#include <llvm/LLVMContext.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>

void lambda_p_test::overlay_binder_test::run ()
{
	run_1 ();
}

void lambda_p_test::overlay_binder_test::run_1 ()
{
	llvm::LLVMContext context;
	boost::shared_ptr <lambda_p_llvm::overlay_binder> overlay (new lambda_p_llvm::overlay_binder);
	boost::shared_ptr <lambda_p_llvm::module> module (new lambda_p_llvm::module (new llvm::Module (llvm::StringRef ("test"), context)));
	llvm::EngineBuilder builder (module->module_m);
	builder.setEngineKind (llvm::EngineKind::JIT);
	boost::shared_ptr <lambda_p_llvm::execution_engine> engine (new lambda_p_llvm::execution_engine (builder.create ()));
	lambda_p::builder builder2;
	builder2 (L"; overlay module engine; overlay module engine; ; :;");
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (builder2.routines.routines->operator[] (0)));
	lambda_p::binder::node_list nodes;
	nodes [routine->routine_m->surface->declarations [0]] = overlay;
	nodes [routine->routine_m->surface->declarations [1]] = engine;
	nodes [routine->routine_m->surface->declarations [2]] = module;
	lambda_p_kernel::apply apply;
	lambda_p::errors::error_list problems;
	lambda_p::binder::node_list declarations;
	apply.core (*routine, nodes, problems, declarations);
	assert (problems.errors.empty ());
	assert (declarations.nodes.size () == 0);
}