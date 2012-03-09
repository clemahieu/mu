#include "create.h"

#include <mu/llvm_/pointer_type/node.h>
#include <mu/llvm_/value/node.h>
#include <mu/script/check.h>

#include <llvm/Constants.h>

#include <boost/make_shared.hpp>

void mu::llvm_::null::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::pointer_type::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::pointer_type::node> (context_a.parameters [0]));
		context_a.results.push_back (boost::make_shared <mu::llvm_::value::node> (llvm::ConstantPointerNull::get (one->pointer_type ()), one));
	}
}