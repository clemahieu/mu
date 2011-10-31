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
#include <lambda_p_llvm/wprintf_function.h>
#include <lambda_p_llvm/malloc_function.h>
#include <lambda_p_llvm/memcpy_function.h>
#include <lambda_p_llvm/abort_function.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_repl/exec_binder.h>
#include <lambda_p_repl/api.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p_repl/repl.h>
#include <lambda_p_kernel/package.h>

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

lambda_p_repl::entry_environment::entry_environment (lambda_p_repl::repl * repl_a)
: repl (repl_a)
{    
}

lambda_p_repl::entry_environment::entry_environment ()
	: repl (nullptr)
{
}

void lambda_p_repl::entry_environment::operator () (boost::shared_ptr <lambda_p_llvm::context> context_instance, lambda_p_llvm::generation_context & context, boost::shared_ptr <lambda_p::core::routine> routine_a)
{	
	llvm::Module * module (context.module);
	llvm::EngineBuilder builder (module);
    builder.setEngineKind (llvm::EngineKind::JIT);
    std::string error;
    builder.setErrorStr (&error);
    llvm::ExecutionEngine * engine = builder.create ();
    lambda_p_llvm::wprintf_function wprintf (context);
    module->getFunctionList ().push_back (wprintf.wprintf);
    engine->addGlobalMapping (wprintf.wprintf, (void *)::wprintf);
    lambda_p_llvm::malloc_function malloc (context);
    module->getFunctionList ().push_back (malloc.malloc);
    engine->addGlobalMapping (malloc.malloc, (void *)::malloc);
    lambda_p_llvm::memcpy_function memcpy (context);
    module->getFunctionList ().push_back (memcpy.memcpy);
	llvm::FunctionType * start_type (llvm::FunctionType::get (llvm::Type::getVoidTy (context.context), false));
    llvm::Function * start (llvm::Function::Create (start_type, llvm::GlobalValue::ExternalLinkage));
    module->getFunctionList ().push_back (start);
	lambda_p_llvm::abort_function abort (context);
	engine->addGlobalMapping (abort.abort, (void *)::abort);
    llvm::BasicBlock * block (llvm::BasicBlock::Create (context.context));
    start->getBasicBlockList ().push_back (block);
    context.block = block;
	lambda_p_repl::api api (context, wprintf, malloc, abort, memcpy);	
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (routine_a));
	boost::shared_ptr <lambda_p::binder::node_list> nodes (new lambda_p::binder::node_list);
	nodes->operator[] (0) = api.package;	
	//if (repl != nullptr)
	//{
 //       std::vector <llvm::Type const *> parameters;
 //       parameters.push_back (llvm::Type::getInt8PtrTy (context.context, 0));
 //       llvm::Function * quit_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context.context), parameters, false), llvm::GlobalValue::ExternalLinkage));
 //       context.module->getFunctionList ().push_back (quit_function);
 //       engine->addGlobalMapping (quit_function, (void *)&quit_invoke);
 //       llvm::GlobalVariable * quit_object (new llvm::GlobalVariable (llvm::Type::getInt8Ty (context.context), true, llvm::GlobalValue::ExternalLinkage));
 //       context.module->getGlobalList ().push_back (quit_object);
 //       engine->addGlobalMapping (quit_object, repl);
	//	boost::shared_ptr <lambda_p_repl::repl_quit_binder> binder (new lambda_p_repl::repl_quit_binder (context, quit_function, quit_object));
	//	nodes->operator[] (1) = binder;
	//}
	boost::shared_ptr <lambda_p_repl::exec_binder> exec_binder (new lambda_p_repl::exec_binder (*nodes.get ()));
	nodes->operator[] (2) = exec_binder;
	exec_binder->nodes.operator[] (2) = exec_binder;
	std::wstring exec_name (L"exec");
	lambda_p::errors::error_list problems;
	lambda_p_kernel::apply apply;
	apply.core (*routine, *nodes, problems);
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
        llvm::ReturnInst * ret (llvm::ReturnInst::Create (context.context));
		context.block->getInstList ().push_back (ret);
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