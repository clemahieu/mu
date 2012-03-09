#include "create_jit.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/execution_engine/node.h>
#include <mu/script/check.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>

#include <sstream>

void mu::llvm_::execution_engine::create_jit::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::module::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::module::node> (context_a.parameters [0]));
		llvm::EngineBuilder builder (one->module);
		builder.setEngineKind (llvm::EngineKind::JIT);
		std::string errors_l;
		builder.setErrorStr (&errors_l);
		auto engine (builder.create ());
		if (engine != nullptr && errors_l.empty ())
		{
			context_a.results.push_back (boost::shared_ptr <mu::core::node> (new mu::llvm_::execution_engine::node (engine)));
		}
		else
		{
			std::wstringstream message;
			message << L"Unable to build ExecutionEngine: ";
			std::wstring error (errors_l.begin (), errors_l.end ());
			message << error;
			(*context_a.errors) (message.str ());
		}
	}
}

std::wstring mu::llvm_::execution_engine::create_jit::name ()
{
	return std::wstring (L"mu::llvm_::execution_engine::create_jit");
}