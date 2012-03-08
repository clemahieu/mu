#include "set_name.h"

#include <mu/llvm_/value/node.h>
#include <mu/script/astring/node.h>

#include <llvm/Value.h>
#include <llvm/ADT/Twine.h>

void mu::llvm_::value::set_name::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::astring::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			one->value ()->setName (llvm::Twine (two->string));
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::value::set_name::count ()
{
	return 2;
}