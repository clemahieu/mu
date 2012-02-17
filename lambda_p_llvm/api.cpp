#include "api.h"

#include <lambda_p_io/analyzer/extensions/global.h>
#include <lambda_p_llvm/context/create.h>
#include <lambda_p_llvm/module/add_package.h>
#include <lambda_p_llvm/module/assemble.h>
#include <lambda_p_llvm/module/create.h>
#include <lambda_p_llvm/module/get_function.h>
#include <lambda_p_llvm/execution_engine/create_jit.h>
#include <lambda_p_llvm/execution_engine/run_function.h>
#include <lambda_p_llvm/module/get_package.h>
#include <lambda_p_llvm/linker/link_modules.h>
#include <lambda_p_llvm/compile/operation.h>
#include <lambda_p_llvm/value/get_context.h>
#include <lambda_p_llvm/value/get_type.h>
#include <lambda_p_llvm/integer_type/create.h>
#include <lambda_p_llvm/execution_engine/generic_value/create_int.h>
#include <lambda_p_llvm/analyzer/operation.h>
#include <lambda_p_llvm/cluster/get.h>
#include <lambda_p_llvm/value/set_name.h>
#include <lambda_p_llvm/module/print.h>
#include <lambda_p_llvm/linkage_types/node.h>
#include <lambda_p_llvm/global_value/set_linkage.h>
#include <lambda_p_llvm/module/verify.h>
#include <lambda_p_llvm/synthesizer/create.h>
#include <lambda_p_llvm/synthesizer/merge.h>
#include <lambda_p_llvm/function/create.h>
#include <lambda_p_llvm/function_type/create.h>
#include <lambda_p_llvm/module/add_function.h>
#include <lambda_p_llvm/synthesizer/add.h>

#include <boost/make_shared.hpp>

lambda_p_llvm::api::api ()
{
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/cluster/get"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::cluster::get> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/compile/operation"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::compile::operation> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/context/create"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::context::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/create_jit"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::execution_engine::create_jit> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/run_function"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::execution_engine::run_function> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/generic_value/create_int"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::execution_engine::generic_value::create_int> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/function/create"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::function::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/function_type/create"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::function_type::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/global_value/set_linkage"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::global_value::set_linkage> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/integer_type/create"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::integer_type::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/linkage_types/external"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::linkage_types::node> (llvm::GlobalValue::ExternalLinkage))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/linker/link_modules"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::linker::link_modules> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/add_function"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::module::add_function> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/add_package"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::module::add_package> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/assemble"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::module::assemble> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/create"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::module::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_function"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::module::get_function> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_package"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::module::get_package> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/print"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::module::print> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/verify"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::module::verify> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/synthesizer/add"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::synthesizer::add> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/synthesizer/create"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::synthesizer::create> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/synthesizer/merge"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::synthesizer::merge> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/value/get_context"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::value::get_context> ())));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/value/set_name"), boost::make_shared <lambda_p_io::analyzer::extensions::global> (boost::make_shared <lambda_p_llvm::value::set_name> ())));
}
