#include "api.h"

#include <lambda_p_kernel/package.h>
#include <lambda_p_llvm/context_binder.h>
#include <lambda_p_llvm/type_binder.h>
#include <lambda_p_llvm/constant_int_binder.h>
#include <lambda_p_llvm/call_inst_binder.h>
#include <lambda_p_llvm/load_inst_binder.h>
#include <lambda_p_llvm/store_inst_binder.h>
#include <lambda_p_llvm/cast_inst_binder.h>
#include <lambda_p_llvm/alloca_inst_binder.h>
#include <lambda_p_llvm/generator.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/struct_binder.h>
#include <lambda_p_llvm/malloc_function.h>
#include <lambda_p_llvm/memcpy_function.h>
#include <lambda_p_llvm/assemble_binder.h>
#include <lambda_p_llvm/overlay_binder.h>
#include <lambda_p_llvm/module_get_function.h>
#include <lambda_p_llvm/jit_function.h>
#include <lambda_p_llvm/execution_engine_binder.h>

#include <llvm/Function.h>

#include <string>

lambda_p_llvm::api::api (llvm::ExecutionEngine * engine_a, lambda_p_llvm::generation_context & context, lambda_p_llvm::malloc_function & malloc, lambda_p_llvm::memcpy_function & memcpy)
	: package (new lambda_p_kernel::package)
{
	std::wstring context_name (L"context");
	boost::shared_ptr <lambda_p_llvm::context_binder> context_binder (new lambda_p_llvm::context_binder);
	package->nodes [context_name] = context_binder;

	std::wstring type_name (L"type");
	boost::shared_ptr <lambda_p_llvm::type_binder> type_binder (new lambda_p_llvm::type_binder);
	package->nodes [type_name] = type_binder;

    std::wstring constant_int_name (L"constant_int");
    boost::shared_ptr <lambda_p_llvm::constant_int_binder> constant_int_binder (new lambda_p_llvm::constant_int_binder);
    package->nodes [constant_int_name] = constant_int_binder;

	std::wstring call_inst_name (L"call_inst");
	boost::shared_ptr <lambda_p_llvm::call_inst_binder> call_inst_binder (new lambda_p_llvm::call_inst_binder (context));
	package->nodes [call_inst_name] = call_inst_binder;

    std::wstring load_inst_name (L"load_inst");
    boost::shared_ptr <lambda_p_llvm::load_inst_binder> load_inst_binder (new lambda_p_llvm::load_inst_binder (context));
    package->nodes [load_inst_name] = load_inst_binder;

    std::wstring store_inst_name (L"store_inst");
    boost::shared_ptr <lambda_p_llvm::store_inst_binder> store_inst_binder (new lambda_p_llvm::store_inst_binder (context));
    package->nodes [store_inst_name] = store_inst_binder;

    std::wstring cast_inst_name (L"cast_inst");
    boost::shared_ptr <lambda_p_llvm::cast_inst_binder> cast_inst_binder (new lambda_p_llvm::cast_inst_binder (context));
    package->nodes [cast_inst_name] = cast_inst_binder;

	std::wstring alloca_inst_name (L"alloca_inst");
	boost::shared_ptr <lambda_p_llvm::alloca_inst_binder> alloca_inst_binder (new lambda_p_llvm::alloca_inst_binder (context));
	package->nodes [alloca_inst_name] = alloca_inst_binder;

	std::wstring generator_name (L"generator");
	boost::shared_ptr <lambda_p_llvm::generator> generator (new lambda_p_llvm::generator);
	package->nodes [generator_name] = generator;
	
	std::wstring malloc_name (L"malloc");
	boost::shared_ptr <lambda_p_llvm::value> malloc_function (new lambda_p_llvm::value (malloc.malloc));
    package->nodes [malloc_name] = malloc_function;
	
    std::wstring memcpy_name (L"memcpy");
    boost::shared_ptr <lambda_p_llvm::value> memcpy_function (new lambda_p_llvm::value (memcpy.memcpy));
    package->nodes [memcpy_name] = memcpy_function;

	std::wstring struct_name (L"struct");
	boost::shared_ptr <lambda_p_llvm::struct_binder> struct_binder (new lambda_p_llvm::struct_binder);
	package->nodes [struct_name] = struct_binder;

	std::wstring overlay_name (L"overlay");
	boost::shared_ptr <lambda_p_llvm::overlay_binder> overlay_binder (new lambda_p_llvm::overlay_binder);
	package->nodes [overlay_name] = overlay_binder;

	std::wstring execution_engine_name (L"execution_engine");
	boost::shared_ptr <lambda_p_llvm::execution_engine_binder> execution_engine_binder (new lambda_p_llvm::execution_engine_binder);
	package->nodes [execution_engine_name] = execution_engine_binder;

	std::wstring assemble_name (L"assemble");
	boost::shared_ptr <lambda_p_llvm::assemble_binder> assemble_binder (new lambda_p_llvm::assemble_binder);
	package->nodes [assemble_name] = assemble_binder;

	std::wstring module_get_function_name (L"module_get_function");
	boost::shared_ptr <lambda_p_llvm::module_get_function> module_get_function_binder (new lambda_p_llvm::module_get_function);
	package->nodes [module_get_function_name] = module_get_function_binder;

	std::wstring jit_function_name (L"jit_function");
	boost::shared_ptr <lambda_p_llvm::jit_function> jit_function_binder (new lambda_p_llvm::jit_function);
	package->nodes [jit_function_name] = jit_function_binder;
}
