#include "create.h"

#include <mu/llvm_/context/node.h>
#include <mu/llvm_/module/node.h>
#include <mu/script/check.h>

#include <llvm/Module.h>

void mu::llvm_::module::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::context::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::context::node> (context_a.parameters [0]));
		context_a.results.push_back (boost::shared_ptr <mu::core::node> (new mu::llvm_::module::node (new llvm::Module (llvm::StringRef (), *one->context))));
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