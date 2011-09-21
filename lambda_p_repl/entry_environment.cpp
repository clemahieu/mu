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

#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/binder/command_list.h>
#include <lambda_p/binder/structure.h>
#include <lambda_p_llvm/data_to_string_binder.h>
#include <lambda_p_repl/repl_quit_binder.h>
#include <lambda_p_repl/repl_quit.h>
#include <lambda_p_repl/hello_world_binder.h>
#include <lambda_p_repl/echo_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_repl/stream_read_entry_routine_binder.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/wprintf_function.h>

#include <llvm/LLVMContext.h>
#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Instructions.h>

lambda_p_repl::entry_environment::entry_environment (::boost::shared_ptr < ::lambda_p_repl::repl_quit> quit_binder_a)
: quit (quit_binder_a)
{    
}

lambda_p_repl::entry_environment::entry_environment ()
{
}

void lambda_p_repl::entry_environment::operator () (::boost::shared_ptr < ::lambda_p::core::routine> routine_a)
{	
    ::llvm::LLVMContext llvm_context;
    ::std::string module_name_string ("llvm_repl");
    ::llvm::StringRef module_name (module_name_string);
    ::llvm::Module * module (new ::llvm::Module (module_name, llvm_context));
    ::lambda_p_llvm::generation_context context (llvm_context, module, NULL);
    ::llvm::EngineBuilder builder (module);
    builder.setEngineKind (::llvm::EngineKind::JIT);
    ::std::string error;
    builder.setErrorStr (&error);
    ::llvm::ExecutionEngine * engine = builder.create ();
    ::lambda_p_llvm::wprintf_function wprintf (context);
    module->getFunctionList ().push_back (wprintf.wprintf);
    engine->addGlobalMapping (wprintf.wprintf, (void *)::wprintf);
    ::llvm::FunctionType * start_type (::llvm::FunctionType::get (::llvm::Type::getVoidTy (llvm_context), false));
    ::llvm::Function * start (::llvm::Function::Create (start_type, ::llvm::GlobalValue::ExternalLinkage));
    module->getFunctionList ().push_back (start);
    ::llvm::BasicBlock * block (::llvm::BasicBlock::Create (llvm_context));
    start->getBasicBlockList ().push_back (block);
    context.block = block;
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::binder::structure> dereference_binder (new ::lambda_p::binder::structure);
	::boost::shared_ptr < ::lambda_p::binder::command_list> commands (new ::lambda_p::binder::command_list);
	::boost::shared_ptr < ::lambda_p_repl::hello_world_binder> hello_binder (new ::lambda_p_repl::hello_world_binder (wprintf.wprintf, context));
	::boost::shared_ptr < ::lambda_p_repl::echo_binder> echo_binder (new ::lambda_p_repl::echo_binder (wprintf.wprintf, context));
	::boost::shared_ptr < ::lambda_p_llvm::data_to_string_binder> d2s_binder (new ::lambda_p_llvm::data_to_string_binder (context));
	::boost::shared_ptr < ::lambda_p_repl::stream_read_entry_routine_binder> read_binder (new ::lambda_p_repl::stream_read_entry_routine_binder);
	::std::wstring echo_name (L"echo");
	::std::wstring hello_name (L"hello");
	::std::wstring d2s_name (L"d2s");
	::std::wstring read_name (L"read");
	dereference_binder->nodes [echo_name] = echo_binder;
	dereference_binder->nodes [hello_name] = hello_binder;
	dereference_binder->nodes [d2s_name] = d2s_binder;
	dereference_binder->nodes [read_name] = read_binder;
	routine_binder.instances [environment_node (routine_a)] = dereference_binder;
	if (quit.get () != NULL)
	{
        ::std::vector < ::llvm::Type const *> parameters;
        parameters.push_back (::llvm::Type::getInt8PtrTy (context.context, 0));
        ::llvm::Function * quit_function (::llvm::Function::Create (::llvm::FunctionType::get (::llvm::Type::getVoidTy (context.context), parameters, false), ::llvm::GlobalValue::ExternalLinkage));
        context.module->getFunctionList ().push_back (quit_function);
        engine->addGlobalMapping (quit_function, (void *)&quit_invoke);
        ::llvm::GlobalVariable * quit_object (new ::llvm::GlobalVariable (::llvm::Type::getInt8PtrTy (context.context), true, ::llvm::GlobalValue::ExternalLinkage));
        context.module->getGlobalList ().push_back (quit_object);
        engine->addGlobalMapping (quit_object, quit.get ());
		::boost::shared_ptr < ::lambda_p_repl::repl_quit_binder> binder (new ::lambda_p_repl::repl_quit_binder (context, quit_function, quit_object));
		::std::wstring quit_name (L"quit");
		dereference_binder->nodes [quit_name] = binder;
	}
	routine_binder (routine_a);
	if (routine_binder.error ())
	{
		::std::wcout << "Binding error:\n";
		::std::wstring message;
		routine_binder.error_message (message);
		::std::wcout << message;
		::std::wcout << '\n';
	}
	else
	{	
        ::llvm::ReturnInst * ret (::llvm::ReturnInst::Create (llvm_context));
        block->getInstList ().push_back (ret);
        commands->operator() ();
        ::std::vector < ::llvm::GenericValue> start_arguments;
        engine->runFunction (start, start_arguments);
	}
}

::lambda_p::core::node * lambda_p_repl::entry_environment::environment_node (::boost::shared_ptr < ::lambda_p::core::routine> routine)
{
	::lambda_p::core::node * result (routine->statements [0]->arguments [0]);
	return result;
}

void ::lambda_p_repl::entry_environment::quit_invoke (void * object)
{
    ::lambda_p_repl::repl_quit * quit (reinterpret_cast < ::lambda_p_repl::repl_quit *> (object));
    quit->operator () ();
}