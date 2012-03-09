#include "create.h"

#include <mu/llvm_/context/value.h>
#include <mu/script/check.h>

void mu::llvm_::context::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <> () (context_a))
	{
		context_a.results.push_back (boost::shared_ptr <mu::core::node> (new mu::llvm_::context::value));
	}
}

std::wstring mu::llvm_::context::create::name ()
{
	return std::wstring (L"mu::llvm_::context::create");
}