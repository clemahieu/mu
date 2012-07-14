#include <mu/llvm_/module/create.h>

#include <mu/llvm_/context/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/check.h>

#include <llvm/Module.h>

#include <gc_cpp.h>

bool mu::llvm_::module::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::llvm_::context::node> () (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		context_a.push (new (GC) mu::llvm_::module::node (new llvm::Module (llvm::StringRef (), *one->context)));
	}
	return valid;
}

std::wstring mu::llvm_::module::create::name ()
{
	return std::wstring (L"mu::llvm_::module::create");
}