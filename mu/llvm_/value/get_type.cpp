#include <mu/llvm_/value/get_type.h>

#include <mu/llvm_/value/node.h>
#include <mu/llvm_/type/build.h>
#include <mu/llvm_/type/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

#include <llvm/Value.h>

#include <gc_cpp.h>

bool mu::llvm_::value::get_type::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::value::node> () (context_a));
	if (result)
	{
		auto one (static_cast <mu::llvm_::value::node *> (context_a.parameters (0)));
		mu::llvm_::type::build build (new (GC) mu::llvm_::context::node (&one->value ()->getContext ()), one->value ()->getType ());
		context_a.push (build.type);
	}
	return result;
}