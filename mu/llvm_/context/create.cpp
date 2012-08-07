#include <mu/llvm_/context/create.h>

#include <mu/llvm_/context/value.h>
#include <mu/script/check.h>

#include <gc_cpp.h>

bool mu::llvm_::context::create::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <> (context_a));
	if (valid)
	{
		context_a.push (new (GC) mu::llvm_::context::value);
	}
	return valid;
}

mu::string mu::llvm_::context::create::name ()
{
	return mu::string (U"mu::llvm_::context::create");
}