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
#include <lambda_p_llvm/value/get_type.h>
#include <lambda_p_llvm/integer_type/create.h>
#include <lambda_p_llvm/execution_engine/generic_value/create_int.h>
#include <lambda_p_llvm/instructions/add.h>
#include <lambda_p_llvm/instructions/and.h>
#include <lambda_p_llvm/instructions/ashr.h>
#include <lambda_p_llvm/instructions/cmpxchg.h>
#include <lambda_p_llvm/instructions/load.h>
#include <lambda_p_llvm/instructions/lshr.h>
#include <lambda_p_llvm/instructions/mul.h>
#include <lambda_p_llvm/instructions/or.h>
#include <lambda_p_llvm/instructions/sdiv.h>
#include <lambda_p_llvm/instructions/shl.h>
#include <lambda_p_llvm/instructions/srem.h>
#include <lambda_p_llvm/instructions/store.h>
#include <lambda_p_llvm/instructions/sub.h>
#include <lambda_p_llvm/instructions/udiv.h>
#include <lambda_p_llvm/instructions/urem.h>
#include <lambda_p_llvm/instructions/xor.h>

lambda_p_llvm::api::api ()
{
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/compile/operation"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::compile::operation)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/context/create"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::context::create)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/create_jit"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::execution_engine::create_jit)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/run_function"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::execution_engine::run_function)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/execution_engine/generic_value/create_int"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::execution_engine::generic_value::create_int)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/add"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::add)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/and"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::and)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/ashr"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::ashr)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/cmpxchg"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::cmpxchg)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/load"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::load)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/lshr"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::lshr)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/mul"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::mul)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/or"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::or)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/sdiv"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::sdiv)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/shl"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::shl)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/srem"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::srem)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/store"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::store)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/sub"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::sub)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/udiv"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::udiv)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/urem"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::urem)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/instructions/xor"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::instructions::xor)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/integer_type/create"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::integer_type::create)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/linker/link_modules"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::linker::link_modules)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/add_package"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::add_package)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/assemble"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::assemble)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/create"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::create)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_function"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::get_function)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/module/get_package"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::module::get_package)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/identity/operation"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::identity::operation)))));
	extensions.insert (std::map <std::wstring, boost::shared_ptr <lambda_p_io::analyzer::extensions::extension>>::value_type (std::wstring (L"llvm/value/get_type"), boost::shared_ptr <lambda_p_io::analyzer::extensions::extension> (new lambda_p_io::analyzer::extensions::global (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::value::get_type)))));
}
