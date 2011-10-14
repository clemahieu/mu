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

#include <lambda_p/binder/bind_procedure.h>
#include <lambda_p/binder/package.h>
#include <lambda_p_llvm/data_to_string_binder.h>
#include <lambda_p_repl/repl_quit_binder.h>
#include <lambda_p_repl/repl.h>
#include <lambda_p_repl/hello_world_binder.h>
#include <lambda_p_repl/echo_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_repl/stream_read_entry_routine_binder.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p_llvm/wprintf_function.h>
#include <lambda_p_llvm/api.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_repl/dynamic_wprintf.h>
#include <lambda_p_llvm/malloc_function.h>
#include <lambda_p_llvm/load_inst_binder.h>
#include <lambda_p_llvm/store_inst_binder.h>
#include <lambda_p_llvm/cast_inst_binder.h>
#include <lambda_p_llvm/memcpy_function.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/while_call_binder.h>
#include <lambda_p_repl/abort_function.h>
#include <lambda_p/binder/single_bind_routine.h>
#include <lambda_p/binder/routine.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/binder/routine_instances_binder.h>
#include <lambda_p_repl/file_routine.h>
#include <lambda_p_llvm/literal_value.h>
#include <lambda_p_llvm/noop_closure_binder.h>
#include <lambda_p_llvm/call_binder.h>

#include <llvm/LLVMContext.h>
#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Instructions.h>

lambda_p_repl::entry_environment::entry_environment (::lambda_p_repl::repl * repl_a)
: repl (repl_a)
{    
}

lambda_p_repl::entry_environment::entry_environment ()
	: repl (NULL)
{
}

void lambda_p_repl::entry_environment::operator () (::boost::shared_ptr < ::lambda_p::core::routine> routine_a)
{	
	::boost::shared_ptr < ::lambda_p_llvm::context> context_instance (new ::lambda_p_llvm::context);
    ::std::string module_name_string ("llvm_repl");
    ::llvm::StringRef module_name (module_name_string);
	::llvm::Module * module (new ::llvm::Module (module_name, context_instance->context_m));
    ::lambda_p_llvm::generation_context context (context_instance->context_m, module, NULL);
    ::llvm::EngineBuilder builder (module);
    builder.setEngineKind (::llvm::EngineKind::JIT);
    ::std::string error;
    builder.setErrorStr (&error);
    ::llvm::ExecutionEngine * engine = builder.create ();
    ::lambda_p_llvm::wprintf_function wprintf (context);
    module->getFunctionList ().push_back (wprintf.wprintf);
    engine->addGlobalMapping (wprintf.wprintf, (void *)::wprintf);
    ::lambda_p_llvm::malloc_function malloc (context);
    module->getFunctionList ().push_back (malloc.malloc);
    engine->addGlobalMapping (malloc.malloc, (void *)::malloc);
    ::lambda_p_llvm::memcpy_function memcpy (context);
    module->getFunctionList ().push_back (memcpy.memcpy);
	::llvm::FunctionType * start_type (::llvm::FunctionType::get (::llvm::Type::getVoidTy (context.context), false));
    ::llvm::Function * start (::llvm::Function::Create (start_type, ::llvm::GlobalValue::ExternalLinkage));
    module->getFunctionList ().push_back (start);
	::lambda_p_repl::abort_function abort (context);
	engine->addGlobalMapping (abort.abort, (void *)::abort);
    ::llvm::BasicBlock * block (::llvm::BasicBlock::Create (context.context));
    start->getBasicBlockList ().push_back (block);
    context.block = block;
	::boost::shared_ptr < ::lambda_p::binder::package> package (new ::lambda_p::binder::package);
	::boost::shared_ptr < ::lambda_p_repl::hello_world_binder> hello_binder (new ::lambda_p_repl::hello_world_binder (wprintf.wprintf, context));
	::boost::shared_ptr < ::lambda_p_repl::echo_binder> echo_binder (new ::lambda_p_repl::echo_binder (wprintf.wprintf, context));
	::boost::shared_ptr < ::lambda_p_llvm::data_to_string_binder> d2s_binder (new ::lambda_p_llvm::data_to_string_binder (context));
	::boost::shared_ptr < ::lambda_p_repl::stream_read_entry_routine_binder> read_binder (new ::lambda_p_repl::stream_read_entry_routine_binder);
	::boost::shared_ptr < ::lambda_p_repl::dynamic_wprintf> wprintf_binder (new ::lambda_p_repl::dynamic_wprintf (wprintf.wprintf, context));
    ::boost::shared_ptr < ::lambda_p_llvm::literal_value> memcpy_function (new ::lambda_p_llvm::literal_value (memcpy.memcpy));
	::boost::shared_ptr < ::lambda_p_llvm::literal_value> malloc_function (new ::lambda_p_llvm::literal_value (malloc.malloc));
	::boost::shared_ptr < ::lambda_p_llvm::while_call_binder> while_binder (new ::lambda_p_llvm::while_call_binder (context));
	::boost::shared_ptr < ::lambda_p_llvm::literal_value> abort_function (new ::lambda_p_llvm::literal_value (abort.abort));
	::boost::shared_ptr < ::lambda_p::binder::routine_binder> binder_function (new ::lambda_p::binder::routine_binder);
	::boost::shared_ptr < ::lambda_p::binder::routine_instances_binder> instances_binder (new ::lambda_p::binder::routine_instances_binder);
	::boost::shared_ptr < ::lambda_p_repl::file_routine> file_binder (new ::lambda_p_repl::file_routine);
	::boost::shared_ptr < ::lambda_p_llvm::noop_closure_binder> noop_closure_binder (new ::lambda_p_llvm::noop_closure_binder (context));
	::boost::shared_ptr < ::lambda_p_llvm::call_binder> call_binder (new ::lambda_p_llvm::call_binder);
	::lambda_p_llvm::api llvm_binder (context);
	::std::wstring echo_name (L"echo");
	::std::wstring hello_name (L"hello");
	::std::wstring d2s_name (L"d2s");
	::std::wstring read_name (L"read");
	::std::wstring llvm_name (L"llvm");
	::std::wstring context_name (L"context");
	::std::wstring wprintf_name (L"wprintf");
    ::std::wstring memcpy_name (L"memcpy");
	::std::wstring malloc_name (L"malloc");
	::std::wstring while_name (L"while");
	::std::wstring abort_name (L"abort");
	::std::wstring binder_name (L"bind");
	::std::wstring instances_name (L"instances");
	::std::wstring file_name (L"file");
	::std::wstring noop_closure_name (L"closen");
	::std::wstring call_binder_name (L"call");
	package->nodes [echo_name] = echo_binder;
	package->nodes [hello_name] = hello_binder;
	package->nodes [d2s_name] = d2s_binder;
	package->nodes [read_name] = read_binder;
	package->nodes [llvm_name] = llvm_binder.package;
	package->nodes [context_name] = context_instance;
	package->nodes [wprintf_name] = wprintf_binder;
    package->nodes [malloc_name] = malloc_function;
    package->nodes [memcpy_name] = memcpy_function;
	package->nodes [while_name] = while_binder;
	package->nodes [abort_name] = abort_function;
	package->nodes [binder_name] = binder_function;
	package->nodes [instances_name] = instances_binder;
	package->nodes [file_name] = file_binder;
	package->nodes [noop_closure_name] = noop_closure_binder;
	package->nodes [call_binder_name] = call_binder;
	if (repl != NULL)
	{
        ::std::vector < ::llvm::Type const *> parameters;
        parameters.push_back (::llvm::Type::getInt8PtrTy (context.context, 0));
        ::llvm::Function * quit_function (::llvm::Function::Create (::llvm::FunctionType::get (::llvm::Type::getVoidTy (context.context), parameters, false), ::llvm::GlobalValue::ExternalLinkage));
        context.module->getFunctionList ().push_back (quit_function);
        engine->addGlobalMapping (quit_function, (void *)&quit_invoke);
        ::llvm::GlobalVariable * quit_object (new ::llvm::GlobalVariable (::llvm::Type::getInt8Ty (context.context), true, ::llvm::GlobalValue::ExternalLinkage));
        context.module->getGlobalList ().push_back (quit_object);
        engine->addGlobalMapping (quit_object, repl);
		::boost::shared_ptr < ::lambda_p_repl::repl_quit_binder> binder (new ::lambda_p_repl::repl_quit_binder (context, quit_function, quit_object));
		::std::wstring quit_name (L"quit");
		package->nodes [quit_name] = binder;
	}
	::boost::shared_ptr < ::lambda_p::binder::routine > routine (new ::lambda_p::binder::routine (routine_a));
	::boost::shared_ptr < ::lambda_p::binder::routine_instances> instances (new ::lambda_p::binder::routine_instances);
	(*instances) [0] = package;
	::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > problems;
	::lambda_p::binder::single_bind_routine bind (routine, instances);
	bind (problems);
	if (!problems.empty ())
	{
		::std::wcout << "Binding error:\n";
		::std::wstringstream stream;
		for (::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> >::iterator i = problems.begin (); i != problems.end (); ++i)
		{
			(*i)->string (stream);
			stream << L'\n';
		}
		stream.seekg (0);
		::std::wstring error (stream.str ());
		::std::wcout << error;
		::std::wcout << '\n';
	}
	else
	{	
        ::llvm::ReturnInst * ret (::llvm::ReturnInst::Create (context.context));
		context.block->getInstList ().push_back (ret);
        ::std::vector < ::llvm::GenericValue> start_arguments;
        engine->runFunction (start, start_arguments);
	}
}

size_t lambda_p_repl::entry_environment::environment_node (::boost::shared_ptr < ::lambda_p::core::routine> routine)
{
	size_t result (routine->surface->results [0]);
	return result;
}

void ::lambda_p_repl::entry_environment::quit_invoke (void * object)
{
    ::lambda_p_repl::repl * repl (reinterpret_cast < ::lambda_p_repl::repl *> (object));
    repl->stop ();
}