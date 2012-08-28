#include <boost/cstdint.hpp>

#include <mu/script/parser_scope_node.h>
#include <mu/llvm_/apint_create.h>
#include <mu/llvm_/cluster_get.h>
#include <mu/llvm_/compile_operation.h>
#include <mu/llvm_/context_create.h>
#include <mu/llvm_/execution_engine_create_jit.h>
#include <mu/llvm_/execution_engine_run_function.h>
#include <mu/llvm_/execution_engine_generic_value_create_int.h>
#include <mu/llvm_/function_create.h>
#include <mu/llvm_/function_type_create.h>
#include <mu/llvm_/global_value_set_linkage.h>
#include <mu/llvm_/global_variable_create.h>
#include <mu/llvm_/integer_type_create.h>
#include <mu/llvm_/linkage_types_node.h>
#include <mu/llvm_/linker_link_modules.h>
#include <mu/llvm_/module_add_function.h>
#include <mu/llvm_/module_add_global_variable.h>
#include <mu/llvm_/module_add_package.h>
#include <mu/llvm_/module_assemble.h>
#include <mu/llvm_/module_create.h>
#include <mu/llvm_/module_get_function.h>
#include <mu/llvm_/module_get_package.h>
#include <mu/llvm_/module_merge.h>
#include <mu/llvm_/module_print.h>
#include <mu/llvm_/module_verify.h>
#include <mu/llvm_/pointer_type_create.h>
#include <mu/llvm_/value_get_context.h>
#include <mu/llvm_/value_set_name.h>
#include <mu/io/keywording_extensions.h>

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
	auto result (new (GC) mu::script::parser_scope::node);
    mu::io::keywording::extensions & extensions (*result->extensions);
	extensions (mu::string (U"apint/create"), new (GC) mu::llvm_::apint::create);
	extensions (mu::string (U"cluster/get"), new (GC) mu::llvm_::cluster::get);
	extensions (mu::string (U"compile/operation"), new (GC) mu::llvm_::compile::operation);
	extensions (mu::string (U"context/create"), new (GC) mu::llvm_::context::create);
	extensions (mu::string (U"execution_engine/create_jit"), new (GC) mu::llvm_::execution_engine::create_jit);
	extensions (mu::string (U"execution_engine/run_function"), new (GC) mu::llvm_::execution_engine::run_function);
	extensions (mu::string (U"execution_engine/generic_value/create_int"), new (GC) mu::llvm_::execution_engine::generic_value::create_int);
	extensions (mu::string (U"function/create"), new (GC) mu::llvm_::function::create);
	extensions (mu::string (U"function_type/create"), new (GC) mu::llvm_::function_type::create);
	extensions (mu::string (U"global_value/set_linkage"), new (GC) mu::llvm_::global_value::set_linkage);
	extensions (mu::string (U"global_variable/create"), new (GC) mu::llvm_::global_variable::create);
	extensions (mu::string (U"integer_type/create"), new (GC) mu::llvm_::integer_type::create);
	extensions (mu::string (U"linkage_types/external"), new (GC) mu::llvm_::linkage_types::node (llvm::GlobalValue::ExternalLinkage));
	extensions (mu::string (U"linker/link_modules"), new (GC) mu::llvm_::linker::link_modules);
	extensions (mu::string (U"module/add_function"), new (GC) mu::llvm_::module::add_function);
	extensions (mu::string (U"module/add_global_variable"), new (GC) mu::llvm_::module::add_global_variable);
	extensions (mu::string (U"module/add_package"), new (GC) mu::llvm_::module::add_package);
	extensions (mu::string (U"module/assemble"), new (GC) mu::llvm_::module::assemble);
	extensions (mu::string (U"module/create"), new (GC) mu::llvm_::module::create);
	extensions (mu::string (U"module/get_function"), new (GC) mu::llvm_::module::get_function);
	extensions (mu::string (U"module/get_package"), new (GC) mu::llvm_::module::get_package);
	extensions (mu::string (U"module/merge"), new (GC) mu::llvm_::module::merge);
	extensions (mu::string (U"module/print"), new (GC) mu::llvm_::module::print);
	extensions (mu::string (U"module/verify"), new (GC) mu::llvm_::module::verify);
	extensions (mu::string (U"pointer_type/create"), new (GC) mu::llvm_::pointer_type::create);
	extensions (mu::string (U"value/get_context"), new (GC) mu::llvm_::value::get_context);
	extensions (mu::string (U"value/set_name"), new (GC) mu::llvm_::value::set_name);
	return result;
}