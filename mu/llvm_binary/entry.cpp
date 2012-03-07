#include <boost/cstdint.hpp>

#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/llvm_/analyzer/operation.h>
#include <mu/llvm_/apint/create.h>
#include <mu/llvm_/cluster/get.h>
#include <mu/llvm_/compile/operation.h>
#include <mu/llvm_/context/create.h>
#include <mu/llvm_/execution_engine/create_jit.h>
#include <mu/llvm_/execution_engine/run_function.h>
#include <mu/llvm_/execution_engine/generic_value/create_int.h>
#include <mu/llvm_/function/create.h>
#include <mu/llvm_/function_type/create.h>
#include <mu/llvm_/global_value/set_linkage.h>
#include <mu/llvm_/global_variable/create.h>
#include <mu/llvm_/integer_type/create.h>
#include <mu/llvm_/linkage_types/node.h>
#include <mu/llvm_/linker/link_modules.h>
#include <mu/llvm_/module/add_function.h>
#include <mu/llvm_/module/add_global_variable.h>
#include <mu/llvm_/module/add_package.h>
#include <mu/llvm_/module/assemble.h>
#include <mu/llvm_/module/create.h>
#include <mu/llvm_/module/get_function.h>
#include <mu/llvm_/module/get_package.h>
#include <mu/llvm_/module/merge.h>
#include <mu/llvm_/module/print.h>
#include <mu/llvm_/module/verify.h>
#include <mu/llvm_/pointer_type/create.h>
#include <mu/llvm_/value/get_context.h>
#include <mu/llvm_/value/set_name.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

extern "C"
#ifdef _WIN32
	__declspec (dllexport)
#endif
boost::uint64_t version_554bc0f73fa23e91 = 0x6d6ecf1f10200f;

extern "C"
#ifdef _WIN32
	__declspec (dllexport)
#endif
void * extensions ()
{
	llvm::InitializeNativeTarget ();
	llvm::InitializeNativeTargetAsmPrinter();
	auto result (new mu::script::extensions::node);
	result->extensions->extensions_m [std::wstring (L"analyzer/operation")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::analyzer::operation> ());
	result->extensions->extensions_m [std::wstring (L"apint/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::apint::create> ());
	result->extensions->extensions_m [std::wstring (L"cluster/get")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::cluster::get> ());
	result->extensions->extensions_m [std::wstring (L"compile/operation")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::compile::operation> ());
	result->extensions->extensions_m [std::wstring (L"context/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::context::create> ());
	result->extensions->extensions_m [std::wstring (L"execution_engine/create_jit")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::execution_engine::create_jit> ());
	result->extensions->extensions_m [std::wstring (L"execution_engine/run_function")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::execution_engine::run_function> ());
	result->extensions->extensions_m [std::wstring (L"execution_engine/generic_value/create_int")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::execution_engine::generic_value::create_int> ());
	result->extensions->extensions_m [std::wstring (L"function/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::function::create> ());
	result->extensions->extensions_m [std::wstring (L"function_type/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::function_type::create> ());
	result->extensions->extensions_m [std::wstring (L"global_value/set_linkage")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::global_value::set_linkage> ());
	result->extensions->extensions_m [std::wstring (L"global_variable/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::global_variable::create> ());
	result->extensions->extensions_m [std::wstring (L"integer_type/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::integer_type::create> ());
	result->extensions->extensions_m [std::wstring (L"linkage_types/external")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::linkage_types::node> (llvm::GlobalValue::ExternalLinkage));
	result->extensions->extensions_m [std::wstring (L"linker/link_modules")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::linker::link_modules> ());
	result->extensions->extensions_m [std::wstring (L"module/add_function")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::add_function> ());
	result->extensions->extensions_m [std::wstring (L"module/add_global_variable")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::add_global_variable> ());
	result->extensions->extensions_m [std::wstring (L"module/add_package")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::add_package> ());
	result->extensions->extensions_m [std::wstring (L"module/assemble")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::assemble> ());
	result->extensions->extensions_m [std::wstring (L"module/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::create> ());
	result->extensions->extensions_m [std::wstring (L"module/get_function")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::get_function> ());
	result->extensions->extensions_m [std::wstring (L"module/get_package")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::get_package> ());
	result->extensions->extensions_m [std::wstring (L"module/merge")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::merge> ());
	result->extensions->extensions_m [std::wstring (L"module/print")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::print> ());
	result->extensions->extensions_m [std::wstring (L"module/verify")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::verify> ());
	result->extensions->extensions_m [std::wstring (L"pointer_type/create")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::pointer_type::create> ());
	result->extensions->extensions_m [std::wstring (L"value/get_context")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::value::get_context> ());
	result->extensions->extensions_m [std::wstring (L"value/set_name")] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::value::set_name> ());
	return result;
}