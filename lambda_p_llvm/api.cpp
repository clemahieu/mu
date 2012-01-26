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
#include <lambda_p_llvm/identity/operation.h>
#include <lambda_p_llvm/value/get_context.h>
#include <lambda_p_llvm/value/get_type.h>
#include <lambda_p_llvm/integer_type/create.h>
#include <lambda_p_llvm/execution_engine/generic_value/create_int.h>
#include <lambda_p_llvm/analyzer/operation.h>

lambda_p_llvm::api::api ()
{
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/analyzer"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::analyzer::operation)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/compile/operation"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::compile::operation)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/context/create"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::context::create)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/create_jit"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::execution_engine::create_jit)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/run_function"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::execution_engine::run_function)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/generic_value/create_int"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::execution_engine::generic_value::create_int)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/integer_type/create"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::integer_type::create)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/linker/link_modules"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::linker::link_modules)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/add_package"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::add_package)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/assemble"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::assemble)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/create"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::create)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_function"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::get_function)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_package"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::get_package)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/identity/operation"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::identity::operation)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/value/get_context"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::value::get_context)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/value/get_type"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::value::get_type)))));
}
