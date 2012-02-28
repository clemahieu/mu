#include "api.h"

#include <mu/io/analyzer/extensions/global.h>
#include <mu/llvm_/context/create.h>
#include <mu/llvm_/module/add_package.h>
#include <mu/llvm_/module/assemble.h>
#include <mu/llvm_/module/create.h>
#include <mu/llvm_/module/get_function.h>
#include <mu/llvm_/execution_engine/create_jit.h>
#include <mu/llvm_/execution_engine/run_function.h>
#include <mu/llvm_/module/get_package.h>
#include <mu/llvm_/linker/link_modules.h>
#include <mu/llvm_/compile/operation.h>
#include <mu/llvm_/value/get_context.h>
#include <mu/llvm_/value/get_type.h>
#include <mu/llvm_/integer_type/create.h>
#include <mu/llvm_/execution_engine/generic_value/create_int.h>
#include <mu/llvm_/analyzer/operation.h>
#include <mu/llvm_/cluster/get.h>
#include <mu/llvm_/value/set_name.h>
#include <mu/llvm_/module/print.h>
#include <mu/llvm_/linkage_types/node.h>
#include <mu/llvm_/global_value/set_linkage.h>
#include <mu/llvm_/module/verify.h>
#include <mu/llvm_/synthesizer/create.h>
#include <mu/llvm_/synthesizer/merge.h>
#include <mu/llvm_/function/create.h>
#include <mu/llvm_/function_type/create.h>
#include <mu/llvm_/module/add_function.h>
#include <mu/llvm_/synthesizer/add.h>
#include <mu/llvm_/apint/create.h>
#include <mu/llvm_/pointer_type/create.h>
#include <mu/llvm_/global_variable/create.h>
#include <mu/llvm_/module/add_global_variable.h>
#include <mu/llvm_/analyzer/operation.h>
#include <mu/llvm_/synthesizer/operation.h>
#include <mu/llvm_/module/merge.h>

#include <boost/make_shared.hpp>

mu::llvm_::api::api ()
{
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/analyzer/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::analyzer::operation> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/apint/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::apint::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/cluster/get"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::cluster::get> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/compile/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::compile::operation> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/context/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::context::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/create_jit"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::execution_engine::create_jit> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/run_function"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::execution_engine::run_function> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/generic_value/create_int"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::execution_engine::generic_value::create_int> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/function/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::function::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/function_type/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::function_type::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/global_value/set_linkage"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::global_value::set_linkage> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/global_variable/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::global_variable::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/integer_type/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::integer_type::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/linkage_types/external"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::linkage_types::node> (llvm::GlobalValue::ExternalLinkage))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/linker/link_modules"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::linker::link_modules> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/add_function"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::add_function> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/add_global_variable"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::add_global_variable> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/add_package"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::add_package> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/assemble"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::assemble> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_function"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::get_function> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_package"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::get_package> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/merge"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::merge> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/print"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::print> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/verify"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::module::verify> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/pointer_type/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::pointer_type::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/synthesizer/add"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::synthesizer::add> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/synthesizer/create"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::synthesizer::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/synthesizer/merge"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::synthesizer::merge> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/synthesizer/operation"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::synthesizer::operation> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/value/get_context"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::value::get_context> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <mu::io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/value/set_name"), boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::llvm_::value::set_name> ())));
}
