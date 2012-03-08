#include "create.h"

#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/pointer_type/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Function.h>

void mu::llvm_::function::create::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::function_type::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		context_a.results.push_back (boost::make_shared <mu::llvm_::function::node> (llvm::Function::Create (one->function_type (), llvm::GlobalValue::PrivateLinkage), boost::make_shared <mu::llvm_::pointer_type::node> (one)));
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::function::create::count ()
{
	return 1;
}