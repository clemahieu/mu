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
	(*result->extensions) (mu::string (U"apint/create"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::apint::create));
	(*result->extensions) (mu::string (U"cluster/get"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::cluster::get));
	(*result->extensions) (mu::string (U"compile/operation"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::compile::operation));
	(*result->extensions) (mu::string (U"context/create"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::context::create));
	(*result->extensions) (mu::string (U"execution_engine/create_jit"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::execution_engine::create_jit));
	(*result->extensions) (mu::string (U"execution_engine/run_function"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::execution_engine::run_function));
	(*result->extensions) (mu::string (U"execution_engine/generic_value/create_int"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::execution_engine::generic_value::create_int));
	(*result->extensions) (mu::string (U"function/create"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::function::create));
	(*result->extensions) (mu::string (U"function_type/create"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::function_type::create));
	(*result->extensions) (mu::string (U"global_value/set_linkage"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::global_value::set_linkage));
	(*result->extensions) (mu::string (U"global_variable/create"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::global_variable::create));
	(*result->extensions) (mu::string (U"integer_type/create"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::integer_type::create));
	(*result->extensions) (mu::string (U"linkage_types/external"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::linkage_types::node (llvm::GlobalValue::ExternalLinkage)));
	(*result->extensions) (mu::string (U"linker/link_modules"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::linker::link_modules));
	(*result->extensions) (mu::string (U"module/add_function"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::add_function));
	(*result->extensions) (mu::string (U"module/add_global_variable"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::add_global_variable));
	(*result->extensions) (mu::string (U"module/add_package"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::add_package));
	(*result->extensions) (mu::string (U"module/assemble"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::assemble));
	(*result->extensions) (mu::string (U"module/create"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::create));
	(*result->extensions) (mu::string (U"module/get_function"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::get_function));
	(*result->extensions) (mu::string (U"module/get_package"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::get_package));
	(*result->extensions) (mu::string (U"module/merge"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::merge));
	(*result->extensions) (mu::string (U"module/print"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::print));
	(*result->extensions) (mu::string (U"module/verify"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::module::verify));
	(*result->extensions) (mu::string (U"pointer_type/create"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::pointer_type::create));
	(*result->extensions) (mu::string (U"synthesizer/operation"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::synthesizer::operation));
	(*result->extensions) (mu::string (U"value/get_context"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::value::get_context));
	(*result->extensions) (mu::string (U"value/set_name"), new (GC) mu::io::analyzer::extensions::global (new (GC) mu::llvm_::value::set_name));
	return result;
}