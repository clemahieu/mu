#include "api.h"

#include <lambda_p_io/analyzer/extensions/global.h>
#include <lambda_p_llvm_wrapper/context/create.h>
#include <lambda_p_llvm_wrapper/module/add_package.h>
#include <lambda_p_llvm_wrapper/module/assemble.h>
#include <lambda_p_llvm_wrapper/module/create.h>
#include <lambda_p_llvm_wrapper/module/get_function.h>
#include <lambda_p_llvm_wrapper/execution_engine/create_jit.h>
#include <lambda_p_llvm_wrapper/execution_engine/run_function.h>
#include <lambda_p_llvm_wrapper/module/get_package.h>
#include <lambda_p_llvm_wrapper/linker/link_modules.h>
#include <lambda_p_llvm_wrapper/compile/operation.h>

lambda_p_llvm_wrapper::api::api ()
{
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/compile/operation"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::compile::operation)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/context/create"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::context::create)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/create_jit"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::execution_engine::create_jit)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/run_function"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::execution_engine::run_function)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/linker/link_modules"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::linker::link_modules)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/add_package"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::module::add_package)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/assemble"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::module::assemble)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/create"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::module::create)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_function"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::module::get_function)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_package"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm_wrapper::module::get_package)))));
}
