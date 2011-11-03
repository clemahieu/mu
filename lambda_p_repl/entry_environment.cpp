//
//  entry_environment.cpp
//  lambda_p_repl
//
//  Created by Colin LeMahieu on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_repl/entry_environment.h>

#include <lambda_p_llvm/context.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_repl/exec_binder.h>
#include <lambda_p_repl/api.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p_repl/repl.h>
#include <lambda_p_kernel/package.h>
#include <lambda_p_repl/overlayed_functions.h>
#include <lambda_p/errors/error.h>
#include <lambda_p/errors/error_list.h>

#include <llvm/LLVMContext.h>
#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Instructions.h>

#include <sstream>

lambda_p_repl::entry_environment::entry_environment (lambda_p_repl::repl * repl_a, boost::shared_ptr <lambda_p_llvm::context> context_instance, boost::shared_ptr <lambda_p_llvm::generation_context> context_a)
: repl (repl_a),
context (context_a)
{	
	llvm::Module * module (context->module);
	llvm::EngineBuilder builder (module);
    builder.setEngineKind (llvm::EngineKind::JIT);
    std::string error;
    builder.setErrorStr (&error);
    engine = builder.create ();
	overlayed_functions overlay (module, context, engine);
	llvm::FunctionType * start_type (llvm::FunctionType::get (llvm::Type::getVoidTy (context->context), false));
    start = llvm::Function::Create (start_type, llvm::GlobalValue::ExternalLinkage);
    module->getFunctionList ().push_back (start);
    llvm::BasicBlock * block (llvm::BasicBlock::Create (context->context));
    start->getBasicBlockList ().push_back (block);
    context->block = block;
	lambda_p_repl::api api (engine, *context, overlay.wprintf, overlay.malloc, overlay.abort, overlay.memcpy);	
	environment = api.package;
	injected_parameters.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"environment"), api.package));	
	boost::shared_ptr <lambda_p_repl::exec_binder> exec_binder (new lambda_p_repl::exec_binder);
	exec = exec_binder;
	exec_binder->set (environment, exec);
	injected_parameters.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"exec"), exec_binder));
}

void lambda_p_repl::entry_environment::run (boost::shared_ptr <lambda_p::core::routine> routine_a)
{
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (routine_a));
	lambda_p::errors::error_list problems;
	lambda_p_kernel::apply apply;
	lambda_p::binder::node_list nodes;
	lambda_p::binder::node_list declarations;
	apply.core (*routine, nodes, problems, declarations);
	if (!problems.errors.empty ())
	{
		std::wcout << "Binding error:\n";
		std::wstringstream stream;
		for (auto i = problems.errors.begin (); i != problems.errors.end (); ++i)
		{
			(*i)->string (stream);
			stream << L'\n';
		}
		stream.seekg (0);
		std::wstring error (stream.str ());
		std::wcout << error;
		std::wcout << '\n';
	}
	else
	{	
        llvm::ReturnInst * ret (llvm::ReturnInst::Create (context->context));
		context->block->getInstList ().push_back (ret);
        std::vector <llvm::GenericValue> start_arguments;
        engine->runFunction (start, start_arguments);
	}
}

size_t lambda_p_repl::entry_environment::environment_node (boost::shared_ptr <lambda_p::core::routine> routine)
{
	size_t result (routine->surface->declarations [0]);
	return result;
}

void lambda_p_repl::entry_environment::quit_invoke (void * object)
{
    lambda_p_repl::repl * repl (reinterpret_cast <lambda_p_repl::repl *> (object));
    repl->stop ();
}