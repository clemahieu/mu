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
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p_llvm/data_to_string_binder.h>
#include <lambda_p_llvm/while_call_binder.h>
#include <lambda_p_llvm/noop_closure_binder.h>
#include <lambda_p_llvm/call_binder.h>
#include <lambda_p_llvm/struct_binder.h>
#include <lambda_p_llvm/malloc_function.h>
#include <lambda_p_llvm/memcpy_function.h>

#include <llvm/Function.h>

#include <string>

lambda_p_llvm::api::api (lambda_p_llvm::generation_context & context, lambda_p_llvm::malloc_function & malloc, lambda_p_llvm::memcpy_function & memcpy)
	: package (new lambda_p_kernel::package)
{
	std::wstring context_name (L"context");
	boost::shared_ptr < lambda_p_llvm::context_binder> context_binder (new lambda_p_llvm::context_binder);
	package->nodes [context_name] = context_binder;

	std::wstring type_name (L"type");
	boost::shared_ptr < lambda_p_llvm::type_binder> type_binder (new lambda_p_llvm::type_binder (context));
	package->nodes [type_name] = type_binder;

    std::wstring constant_int_name (L"constant_int");
    boost::shared_ptr < lambda_p_llvm::constant_int_binder> constant_int_binder (new lambda_p_llvm::constant_int_binder (context));
    package->nodes [constant_int_name] = constant_int_binder;

	std::wstring call_inst_name (L"call_inst");
	boost::shared_ptr < lambda_p_llvm::call_inst_binder> call_inst_binder (new lambda_p_llvm::call_inst_binder (context));
	package->nodes [call_inst_name] = call_inst_binder;

    std::wstring load_inst_name (L"load_inst");
    boost::shared_ptr < lambda_p_llvm::load_inst_binder> load_inst_binder (new lambda_p_llvm::load_inst_binder (context));
    package->nodes [load_inst_name] = load_inst_binder;

    std::wstring store_inst_name (L"store_inst");
    boost::shared_ptr < lambda_p_llvm::store_inst_binder> store_inst_binder (new lambda_p_llvm::store_inst_binder (context));
    package->nodes [store_inst_name] = store_inst_binder;

    std::wstring cast_inst_name (L"cast_inst");
    boost::shared_ptr < lambda_p_llvm::cast_inst_binder> cast_inst_binder (new lambda_p_llvm::cast_inst_binder (context));
    package->nodes [cast_inst_name] = cast_inst_binder;

	std::wstring alloca_inst_name (L"alloca_inst");
	boost::shared_ptr < lambda_p_llvm::alloca_inst_binder> alloca_inst_binder (new lambda_p_llvm::alloca_inst_binder (context));
	package->nodes [alloca_inst_name] = alloca_inst_binder;

	std::wstring generator_name (L"generator");
	boost::shared_ptr <lambda_p_llvm::generator> generator (new lambda_p_llvm::generator (context));
	package->nodes [generator_name] = generator;
	
	std::wstring malloc_name (L"malloc");
	boost::shared_ptr <lambda_p_llvm::fo_value> malloc_function (new lambda_p_llvm::fo_value (malloc.malloc));
    package->nodes [malloc_name] = malloc_function;
	
	std::wstring d2s_name (L"d2s");
	boost::shared_ptr <lambda_p_llvm::data_to_string_binder> d2s_binder (new lambda_p_llvm::data_to_string_binder (context));
	package->nodes [d2s_name] = d2s_binder;
	
    std::wstring memcpy_name (L"memcpy");
    boost::shared_ptr <lambda_p_llvm::fo_value> memcpy_function (new lambda_p_llvm::fo_value (memcpy.memcpy));
    package->nodes [memcpy_name] = memcpy_function;
	
	std::wstring while_name (L"while");
	boost::shared_ptr <lambda_p_llvm::while_call_binder> while_binder (new lambda_p_llvm::while_call_binder (context));
	package->nodes [while_name] = while_binder;
	
	std::wstring noop_closure_name (L"closen");
	boost::shared_ptr <lambda_p_llvm::noop_closure_binder> noop_closure_binder (new lambda_p_llvm::noop_closure_binder (context));
	package->nodes [noop_closure_name] = noop_closure_binder;
	
	std::wstring call_binder_name (L"call");
	boost::shared_ptr <lambda_p_llvm::call_binder> call_binder (new lambda_p_llvm::call_binder);
	package->nodes [call_binder_name] = call_binder;

	std::wstring struct_name (L"struct");
	boost::shared_ptr <lambda_p_llvm::struct_binder> struct_binder (new lambda_p_llvm::struct_binder (context));
	package->nodes [struct_name] = struct_binder;
}
