#include "create.h"

#include <mu/llvm_/type/node.h>
#include <mu/llvm_/global_variable/node.h>

#include <boost/make_shared.hpp>

#include <llvm/GlobalVariable.h>

void mu::llvm_::global_variable::create::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::type::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		context_a.results.push_back (boost::make_shared <mu::llvm_::global_variable::node> (new llvm::GlobalVariable (one->type (), false, llvm::GlobalValue::PrivateLinkage), one));
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::global_variable::create::count ()
{
	return 1;
}