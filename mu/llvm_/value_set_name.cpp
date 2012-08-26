#include <mu/llvm_/value_set_name.h>

#include <mu/llvm_/value_node.h>
#include <mu/script/astring_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <llvm/Value.h>
#include <llvm/ADT/Twine.h>

bool mu::llvm_::value::set_name::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::llvm_::value::node, mu::script::astring::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		auto two (static_cast <mu::script::astring::node *> (context_a.parameters (1)));
		one->value ()->setName (llvm::Twine (two->string));
	}
	return valid;
}