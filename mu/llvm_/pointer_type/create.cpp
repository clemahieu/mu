#include "create.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/apint/node.h>
#include <mu/llvm_/pointer_type/node.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::pointer_type::create::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::type::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		context_a.results.push_back (boost::make_shared <mu::llvm_::pointer_type::node> (one));
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::pointer_type::create::count ()
{
	return 1;
}