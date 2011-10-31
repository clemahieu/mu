#include "api.h"

#include <lambda_p_kernel/package.h>
#include <lambda_p_repl/hello_world_binder.h>
#include <lambda_p_repl/echo_binder.h>
#include <lambda_p_repl/routine_builder_binder.h>
#include <lambda_p_repl/dynamic_wprintf.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_kernel/node_list_binder.h>
#include <lambda_p_kernel/package_add.h>
#include <lambda_p_kernel/package_create.h>
#include <lambda_p_repl/data_stream_binder.h>
#include <lambda_p_repl/file_stream_binder.h>
#include <lambda_p_llvm/api.h>
#include <lambda_p_llvm/wprintf_function.h>
#include <lambda_p_llvm/malloc_function.h>
#include <lambda_p_llvm/api.h>
#include <lambda_p_llvm/abort_function.h>

#include <llvm/Function.h>

#include <llvm/LLVMContext.h>

lambda_p_repl::api::api (lambda_p_llvm::generation_context & context, lambda_p_llvm::wprintf_function & wprintf, lambda_p_llvm::malloc_function & malloc, lambda_p_llvm::abort_function & abort, lambda_p_llvm::memcpy_function & memcpy)
	: package (new lambda_p_kernel::package)
{
	boost::shared_ptr <lambda_p_kernel::package> package_l (new lambda_p_kernel::package);
	boost::shared_ptr <lambda_p_repl::hello_world_binder> hello_binder (new lambda_p_repl::hello_world_binder (wprintf.wprintf, context));
	boost::shared_ptr <lambda_p_repl::echo_binder> echo_binder (new lambda_p_repl::echo_binder (wprintf.wprintf, context));
	boost::shared_ptr <lambda_p_repl::routine_builder_binder> read_binder (new lambda_p_repl::routine_builder_binder);
	boost::shared_ptr <lambda_p_repl::dynamic_wprintf> wprintf_binder (new lambda_p_repl::dynamic_wprintf (wprintf.wprintf, context));
	boost::shared_ptr <lambda_p_kernel::apply> apply_binder (new lambda_p_kernel::apply);
	boost::shared_ptr <lambda_p_kernel::package_add> package_add_binder (new lambda_p_kernel::package_add);
	boost::shared_ptr <lambda_p_kernel::package_create> package_create_binder (new lambda_p_kernel::package_create);
	boost::shared_ptr <lambda_p_repl::data_stream_binder> data_stream_binder (new lambda_p_repl::data_stream_binder);
	boost::shared_ptr <lambda_p_repl::routine_builder_binder> routine_builder_binder (new lambda_p_repl::routine_builder_binder);
	boost::shared_ptr <lambda_p_repl::file_stream_binder> file_stream_binder (new lambda_p_repl::file_stream_binder);
	lambda_p_llvm::api llvm_binder (context, malloc, memcpy);
	std::wstring echo_name (L"echo");
	std::wstring hello_name (L"hello");
	std::wstring read_name (L"read");
	std::wstring llvm_name (L"llvm");
	std::wstring wprintf_name (L"wprintf");
	std::wstring package_create_name (L"package_create");
	std::wstring package_add_name (L"package_add");
	std::wstring data_stream_name (L"data_stream");
	std::wstring routine_builder_binder_name (L"routine_builder");
	std::wstring apply_name (L"apply");
	std::wstring file_stream_name (L"file_stream");
	package->nodes [echo_name] = echo_binder;
	package->nodes [hello_name] = hello_binder;
	package->nodes [read_name] = read_binder;
	package->nodes [llvm_name] = llvm_binder.package;
	package->nodes [wprintf_name] = wprintf_binder;
	package->nodes [package_create_name] = package_create_binder;
	package->nodes [package_add_name] = package_add_binder;
	package->nodes [data_stream_name] = data_stream_binder;
	package->nodes [routine_builder_binder_name] = routine_builder_binder;
	package->nodes [apply_name] = apply_binder;
	package->nodes [file_stream_name] = file_stream_binder;
}