#include "set_name.h"

#include <mu/llvm_/value/node.h>
#include <mu/script/astring/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>
#include <llvm/ADT/Twine.h>

void mu::llvm_::value::set_name::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::value::node, mu::script::astring::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::astring::node> (context_a.parameters [1]));
		one->value ()->setName (llvm::Twine (two->string));
	}
}

size_t mu::llvm_::value::set_name::count ()
{
	return 2;
}