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

#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p_kernel/package.h>
#include <lambda_p_llvm/data_to_string_binder.h>
#include <lambda_p_repl/repl_quit_binder.h>
#include <lambda_p_repl/repl.h>
#include <lambda_p_repl/hello_world_binder.h>
#include <lambda_p_repl/echo_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_repl/routine_builder_binder.h>
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
#include <lambda_p_kernel/single_bind_routine.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_kernel/node_list_binder.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p_llvm/noop_closure_binder.h>
#include <lambda_p_llvm/call_binder.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p_llvm/struct_binder.h>
#include <lambda_p_kernel/package_add.h>
#include <lambda_p_kernel/package_create.h>
#include <lambda_p_repl/data_stream_binder.h>
#include <lambda_p_repl/file_stream_binder.h>
#include <lambda_p_repl/exec_binder.h>

#include <llvm/LLVMContext.h>
#include <llvm/Type.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Instructions.h>

lambda_p_repl::entry_environment::entry_environment (lambda_p_repl::repl * repl_a)
: repl (repl_a)
{    
}

lambda_p_repl::entry_environment::entry_environment ()
	: repl (nullptr)
{
}

void lambda_p_repl::entry_environment::operator () (boost::shared_ptr < lambda_p::core::routine> routine_a)
{	
	boost::shared_ptr <lambda_p_llvm::context> context_instance (new lambda_p_llvm::context);
    std::string module_name_string ("llvm_repl");
    llvm::StringRef module_name (module_name_string);
	llvm::Module * module (new llvm::Module (module_name, context_instance->context_m));
    lambda_p_llvm::generation_context context (context_instance->context_m, module, nullptr);
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
	lambda_p_repl::abort_function abort (context);
	engine->addGlobalMapping (abort.abort, (void *)::abort);
    llvm::BasicBlock * block (llvm::BasicBlock::Create (context.context));
    start->getBasicBlockList ().push_back (block);
    context.block = block;
	boost::shared_ptr <lambda_p_kernel::package> package (new lambda_p_kernel::package);
	boost::shared_ptr <lambda_p_repl::hello_world_binder> hello_binder (new lambda_p_repl::hello_world_binder (wprintf.wprintf, context));
	boost::shared_ptr <lambda_p_repl::echo_binder> echo_binder (new lambda_p_repl::echo_binder (wprintf.wprintf, context));
	boost::shared_ptr <lambda_p_llvm::data_to_string_binder> d2s_binder (new lambda_p_llvm::data_to_string_binder (context));
	boost::shared_ptr <lambda_p_repl::routine_builder_binder> read_binder (new lambda_p_repl::routine_builder_binder);
	boost::shared_ptr <lambda_p_repl::dynamic_wprintf> wprintf_binder (new lambda_p_repl::dynamic_wprintf (wprintf.wprintf, context));
    boost::shared_ptr <lambda_p_llvm::fo_value> memcpy_function (new lambda_p_llvm::fo_value (memcpy.memcpy));
	boost::shared_ptr <lambda_p_llvm::fo_value> malloc_function (new lambda_p_llvm::fo_value (malloc.malloc));
	boost::shared_ptr <lambda_p_llvm::while_call_binder> while_binder (new lambda_p_llvm::while_call_binder (context));
	boost::shared_ptr <lambda_p_llvm::fo_value> abort_function (new lambda_p_llvm::fo_value (abort.abort));
	boost::shared_ptr <lambda_p_kernel::apply> apply_binder (new lambda_p_kernel::apply);
	boost::shared_ptr <lambda_p::binder::node_list_binder> nodes_binder (new lambda_p::binder::node_list_binder);
	boost::shared_ptr <lambda_p_llvm::noop_closure_binder> noop_closure_binder (new lambda_p_llvm::noop_closure_binder (context));
	boost::shared_ptr <lambda_p_llvm::call_binder> call_binder (new lambda_p_llvm::call_binder);
	boost::shared_ptr <lambda_p::binder::list_binder> list_binder (new lambda_p::binder::list_binder);
	boost::shared_ptr <lambda_p_llvm::struct_binder> struct_binder (new lambda_p_llvm::struct_binder (context));
	boost::shared_ptr <lambda_p_kernel::package_add> package_add_binder (new lambda_p_kernel::package_add);
	boost::shared_ptr <lambda_p_kernel::package_create> package_create_binder (new lambda_p_kernel::package_create);
	boost::shared_ptr <lambda_p_repl::data_stream_binder> data_stream_binder (new lambda_p_repl::data_stream_binder);
	boost::shared_ptr <lambda_p_repl::routine_builder_binder> routine_builder_binder (new lambda_p_repl::routine_builder_binder);
	boost::shared_ptr <lambda_p_repl::file_stream_binder> file_stream_binder (new lambda_p_repl::file_stream_binder);
	lambda_p_llvm::api llvm_binder (context);
	std::wstring echo_name (L"echo");
	std::wstring hello_name (L"hello");
	std::wstring d2s_name (L"d2s");
	std::wstring read_name (L"read");
	std::wstring llvm_name (L"llvm");
	std::wstring context_name (L"context");
	std::wstring wprintf_name (L"wprintf");
    std::wstring memcpy_name (L"memcpy");
	std::wstring malloc_name (L"malloc");
	std::wstring while_name (L"while");
	std::wstring abort_name (L"abort");
	std::wstring nodes_name (L"nodes");
	std::wstring noop_closure_name (L"closen");
	std::wstring call_binder_name (L"call");
	std::wstring list_name (L"list");
	std::wstring struct_name (L"struct");
	std::wstring package_create_name (L"package_create");
	std::wstring package_add_name (L"package_add");
	std::wstring data_stream_name (L"data_stream");
	std::wstring routine_builder_binder_name (L"routine_builder");
	std::wstring apply_name (L"apply");
	std::wstring file_stream_name (L"file_stream");
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
	package->nodes [nodes_name] = nodes_binder;
	package->nodes [noop_closure_name] = noop_closure_binder;
	package->nodes [call_binder_name] = call_binder;
	package->nodes [list_name] = list_binder;
	package->nodes [struct_name] = struct_binder;
	package->nodes [package_create_name] = package_create_binder;
	package->nodes [package_add_name] = package_add_binder;
	package->nodes [data_stream_name] = data_stream_binder;
	package->nodes [routine_builder_binder_name] = routine_builder_binder;
	package->nodes [apply_name] = apply_binder;
	package->nodes [file_stream_name] = file_stream_binder;
	boost::shared_ptr <lambda_p_kernel::routine > routine (new lambda_p_kernel::routine (routine_a));
	boost::shared_ptr <lambda_p::binder::node_list> nodes (new lambda_p::binder::node_list);
	nodes->operator[] (0) = package;	
	if (repl != nullptr)
	{
        std::vector <llvm::Type const *> parameters;
        parameters.push_back (llvm::Type::getInt8PtrTy (context.context, 0));
        llvm::Function * quit_function (llvm::Function::Create (llvm::FunctionType::get (llvm::Type::getVoidTy (context.context), parameters, false), llvm::GlobalValue::ExternalLinkage));
        context.module->getFunctionList ().push_back (quit_function);
        engine->addGlobalMapping (quit_function, (void *)&quit_invoke);
        llvm::GlobalVariable * quit_object (new llvm::GlobalVariable (llvm::Type::getInt8Ty (context.context), true, llvm::GlobalValue::ExternalLinkage));
        context.module->getGlobalList ().push_back (quit_object);
        engine->addGlobalMapping (quit_object, repl);
		boost::shared_ptr <lambda_p_repl::repl_quit_binder> binder (new lambda_p_repl::repl_quit_binder (context, quit_function, quit_object));
		nodes->operator[] (1) = binder;
	}
	boost::shared_ptr <lambda_p_repl::exec_binder> exec_binder (new lambda_p_repl::exec_binder (*nodes.get ()));
	nodes->operator[] (2) = exec_binder;
	exec_binder->nodes.operator[] (2) = exec_binder;
	std::wstring exec_name (L"exec");
	lambda_p::errors::error_list problems;
	lambda_p_kernel::single_bind_routine bind (routine, nodes);
	bind (problems);
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