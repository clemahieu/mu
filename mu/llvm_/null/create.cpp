#include "create.h"

#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/value/node.h>

#include <llvm/Constants.h>

#include <boost/make_shared.hpp>

void mu::llvm_::null::create::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		context_a.results.push_back (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantPointerNull::get (one->pointer_type ()), one));
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::null::create::count ()
{
	return 1;
}