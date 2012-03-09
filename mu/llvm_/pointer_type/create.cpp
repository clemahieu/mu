#include "create.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/script/check.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::pointer_type::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::type::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::type::node> (context_a.parameters [0]));
		context_a.results.push_back (boost::make_shared <mu::llvm_::pointer_type::node> (one));
	}
}