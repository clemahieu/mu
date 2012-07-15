#include <boost/cstdint.hpp>

#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/script/extensions/node.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/llvm_/synthesizer/operation.h>
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

#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>

#include <gc_cpp.h>

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
	auto result (new (GC) mu::script::extensions::node);
	result->extensions->extensions_m [std::wstring (L"apint/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::apint::create);
	result->extensions->extensions_m [std::wstring (L"cluster/get")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::cluster::get);
	result->extensions->extensions_m [std::wstring (L"compile/operation")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::compile::operation);
	result->extensions->extensions_m [std::wstring (L"context/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::context::create);
	result->extensions->extensions_m [std::wstring (L"execution_engine/create_jit")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::execution_engine::create_jit);
	result->extensions->extensions_m [std::wstring (L"execution_engine/run_function")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::execution_engine::run_function);
	result->extensions->extensions_m [std::wstring (L"execution_engine/generic_value/create_int")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::execution_engine::generic_value::create_int);
	result->extensions->extensions_m [std::wstring (L"function/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::function::create);
	result->extensions->extensions_m [std::wstring (L"function_type/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::function_type::create);
	result->extensions->extensions_m [std::wstring (L"global_value/set_linkage")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::global_value::set_linkage);
	result->extensions->extensions_m [std::wstring (L"global_variable/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::global_variable::create);
	result->extensions->extensions_m [std::wstring (L"integer_type/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::integer_type::create);
	result->extensions->extensions_m [std::wstring (L"linkage_types/external")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::linkage_types::node (llvm::GlobalValue::ExternalLinkage));
	result->extensions->extensions_m [std::wstring (L"linker/link_modules")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::linker::link_modules);
	result->extensions->extensions_m [std::wstring (L"module/add_function")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::add_function);
	result->extensions->extensions_m [std::wstring (L"module/add_global_variable")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::add_global_variable);
	result->extensions->extensions_m [std::wstring (L"module/add_package")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::add_package);
	result->extensions->extensions_m [std::wstring (L"module/assemble")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::assemble);
	result->extensions->extensions_m [std::wstring (L"module/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::create);
	result->extensions->extensions_m [std::wstring (L"module/get_function")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::get_function);
	result->extensions->extensions_m [std::wstring (L"module/get_package")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::get_package);
	result->extensions->extensions_m [std::wstring (L"module/merge")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::merge);
	result->extensions->extensions_m [std::wstring (L"module/print")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::print);
	result->extensions->extensions_m [std::wstring (L"module/verify")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::verify);
	result->extensions->extensions_m [std::wstring (L"pointer_type/create")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::pointer_type::create);
	result->extensions->extensions_m [std::wstring (L"synthesizer/operation")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::synthesizer::operation);
	result->extensions->extensions_m [std::wstring (L"value/get_context")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::value::get_context);
	result->extensions->extensions_m [std::wstring (L"value/set_name")] = new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::value::set_name);
	return result;
}