#include "create_jit.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/execution_engine/node.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>

#include <sstream>

void mu::llvm_::execution_engine::create_jit::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::module::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		llvm::EngineBuilder builder (one->module);
		builder.setEngineKind (llvm::EngineKind::JIT);
		std::string errors_l;
		builder.setErrorStr (&errors_l);
		auto engine (builder.create ());
		if (engine != nullptr && errors_l.empty ())
		{
			results.push_back (boost::shared_ptr <mu::core::node> (new mu::llvm_::execution_engine::node (engine)));
		}
		else
		{
			std::wstringstream message;
			message << L"Unable to build ExecutionEngine: ";
			std::wstring error (errors_l.begin (), errors_l.end ());
			message << error;
			(*errors_a) (message.str ());
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::execution_engine::create_jit::count ()
{
	return 1;
}

std::wstring mu::llvm_::execution_engine::create_jit::name ()
{
	return std::wstring (L"mu::llvm_::execution_engine::create_jit");
}