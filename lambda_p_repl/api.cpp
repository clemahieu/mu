#include "api.h"

#include <lambda_p_kernel/package.h>
#include <lambda_p_repl/routine_builder_binder.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_kernel/package_add.h>
#include <lambda_p_kernel/package_create.h>
#include <lambda_p_repl/data_stream_binder.h>
#include <lambda_p_repl/file_stream_binder.h>
#include <lambda_p_llvm/api.h>
#include <lambda_p_llvm/wprintf_function.h>
#include <lambda_p_llvm/malloc_function.h>
#include <lambda_p_llvm/api.h>
#include <lambda_p_llvm/abort_function.h>
#include <lambda_p_kernel/directory_compile.h>
#include <lambda_p_kernel/adata_binder.h>
#include <lambda_p_kernel/cvalue.h>
#include <lambda_p_kernel/fapply.h>
#include <lambda_p_kernel/eval.h>
#include <lambda_p_kernel/times.h>
#include <lambda_p_kernel/number_binder.h>
#include <lambda_p/binder/list_binder.h>

#include <llvm/Function.h>

#include <llvm/LLVMContext.h>

lambda_p_repl::api::api (llvm::ExecutionEngine * engine_a, lambda_p_llvm::generation_context & context, lambda_p_llvm::wprintf_function & wprintf, lambda_p_llvm::malloc_function & malloc, lambda_p_llvm::abort_function & abort, lambda_p_llvm::memcpy_function & memcpy)
	: package (new lambda_p_kernel::package)
{
	boost::shared_ptr <lambda_p_kernel::package> package_l (new lambda_p_kernel::package);
	boost::shared_ptr <lambda_p_repl::routine_builder_binder> read_binder (new lambda_p_repl::routine_builder_binder);
	boost::shared_ptr <lambda_p_kernel::apply> apply_binder (new lambda_p_kernel::apply);
	boost::shared_ptr <lambda_p_kernel::package_add> package_add_binder (new lambda_p_kernel::package_add);
	boost::shared_ptr <lambda_p_kernel::package_create> package_create_binder (new lambda_p_kernel::package_create);
	boost::shared_ptr <lambda_p_repl::data_stream_binder> data_stream_binder (new lambda_p_repl::data_stream_binder);
	boost::shared_ptr <lambda_p_repl::routine_builder_binder> routine_builder_binder (new lambda_p_repl::routine_builder_binder);
	boost::shared_ptr <lambda_p_repl::file_stream_binder> file_stream_binder (new lambda_p_repl::file_stream_binder);
	boost::shared_ptr <lambda_p_kernel::directory_compile> directory_compile (new lambda_p_kernel::directory_compile);
	boost::shared_ptr <lambda_p_kernel::adata_binder> adata_binder (new lambda_p_kernel::adata_binder);
	boost::shared_ptr <lambda_p_kernel::cvalue> cvalue_binder (new lambda_p_kernel::cvalue);
	boost::shared_ptr <lambda_p_kernel::fapply> fapply_binder (new lambda_p_kernel::fapply);
	boost::shared_ptr <lambda_p_kernel::eval> eval_binder (new lambda_p_kernel::eval);
	boost::shared_ptr <lambda_p_kernel::times> times_binder (new lambda_p_kernel::times);
	boost::shared_ptr <lambda_p_kernel::number_binder> number_binder (new lambda_p_kernel::number_binder);
	boost::shared_ptr <lambda_p::binder::list_binder> list_binder (new lambda_p::binder::list_binder);
	lambda_p_llvm::api llvm_binder (engine_a, context, malloc, memcpy);
	std::wstring read_name (L"read");
	std::wstring llvm_name (L"llvm");
	std::wstring package_create_name (L"package_create");
	std::wstring package_add_name (L"package_add");
	std::wstring data_stream_name (L"data_stream");
	std::wstring routine_builder_binder_name (L"routine_builder");
	std::wstring apply_name (L"apply");
	std::wstring file_stream_name (L"file_stream");
	std::wstring directory_compile_name (L"directory_compile");
	std::wstring adata_name (L"adata");
	std::wstring cvalue_name (L"cvalue");
	std::wstring fapply_name (L"fapply");
	std::wstring eval_name (L"eval");
	std::wstring times_name (L"times");
	std::wstring number_name (L"number");
	std::wstring list_name (L"list");
	package->nodes [read_name] = read_binder;
	package->nodes [llvm_name] = llvm_binder.package;
	package->nodes [package_create_name] = package_create_binder;
	package->nodes [package_add_name] = package_add_binder;
	package->nodes [data_stream_name] = data_stream_binder;
	package->nodes [routine_builder_binder_name] = routine_builder_binder;
	package->nodes [apply_name] = apply_binder;
	package->nodes [file_stream_name] = file_stream_binder;
	package->nodes [directory_compile_name] = directory_compile;
	package->nodes [adata_name] = adata_binder;
	package->nodes [cvalue_name] = cvalue_binder;
	package->nodes [fapply_name] = fapply_binder;
	package->nodes [eval_name] = eval_binder;
	package->nodes [times_name] = times_binder;
	package->nodes [number_name] = number_binder;
	package->nodes [list_name] = list_binder;
}