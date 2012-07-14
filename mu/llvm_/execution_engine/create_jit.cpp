#include <mu/llvm_/execution_engine/create_jit.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/module/node.h>
#include <mu/llvm_/execution_engine/node.h>
#include <mu/script/check.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::execution_engine::create_jit::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::module::node> () (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::module::node *> (context_a.parameters (0)));
		llvm::EngineBuilder builder (one->module);
		builder.setEngineKind (llvm::EngineKind::JIT);
		std::string errors_l;
		builder.setErrorStr (&errors_l);
		auto engine (builder.create ());
		if (engine != nullptr && errors_l.empty ())
		{
			context_a.push (new (GC) mu::llvm_::execution_engine::node (engine));
		}
		else
		{
			std::wstringstream message;
			message << L"Unable to build ExecutionEngine: ";
			std::wstring error (errors_l.begin (), errors_l.end ());
			message << error;
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}

std::wstring mu::llvm_::execution_engine::create_jit::name ()
{
	return std::wstring (L"mu::llvm_::execution_engine::create_jit");
}