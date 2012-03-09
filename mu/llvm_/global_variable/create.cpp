#include "create.h"

#include <mu/llvm_/type/node.h>
#include <mu/llvm_/global_variable/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

#include <llvm/GlobalVariable.h>

void mu::llvm_::global_variable::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::type::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::type::node> (context_a.parameters [0]));
		context_a.results.push_back (boost::make_shared <mu::llvm_::global_variable::node> (new llvm::GlobalVariable (one->type (), false, llvm::GlobalValue::PrivateLinkage), one));
	}
}