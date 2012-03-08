#include "create.h"

#include <mu/llvm_/context/node.h>
#include <mu/llvm_/module/node.h>

#include <llvm/Module.h>

void mu::llvm_::module::create::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::context::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		context_a.results.push_back (boost::shared_ptr <mu::core::node> (new mu::llvm_::module::node (new llvm::Module (llvm::StringRef (), *one->context))));
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::module::create::count ()
{
	return 1;
}

std::wstring mu::llvm_::module::create::name ()
{
	return std::wstring (L"mu::llvm_::module::create");
}