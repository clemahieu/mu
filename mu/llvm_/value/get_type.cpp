#include "get_type.h"

#include <mu/llvm_/value/node.h>
#include <mu/llvm_/type/build.h>
#include <mu/llvm_/type/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

#include <llvm/Value.h>

void mu::llvm_::value::get_type::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::value::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
		mu::llvm_::type::build build (boost::make_shared <mu::llvm_::context::node> (&one->value ()->getContext ()), one->value ()->getType ());
		context_a.results.push_back (build.type);
	}
}