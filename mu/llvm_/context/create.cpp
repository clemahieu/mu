#include <mu/llvm_/context/create.h>

#include <mu/llvm_/context/value.h>
#include <mu/script/check.h>

bool mu::llvm_::context::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <> () (context_a));
	if (valid)
	{
		context_a.push (boost::shared_ptr <mu::core::node> (new mu::llvm_::context::value));
	}
	return valid;
}

std::wstring mu::llvm_::context::create::name ()
{
	return std::wstring (L"mu::llvm_::context::create");
}