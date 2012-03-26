#include <mu/llvm_/function/create.h>

#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/pointer_type/node.h>
#include <mu/script/check.h>

#include <boost/make_shared.hpp>

#include <llvm/Function.h>

bool mu::llvm_::function::create::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::function_type::node> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::llvm_::function_type::node> (context_a.parameters (0)));
		context_a.push (boost::make_shared <mu::llvm_::function::node> (llvm::Function::Create (one->function_type (), llvm::GlobalValue::PrivateLinkage), boost::make_shared <mu::llvm_::pointer_type::node> (one)));
	}
	return result;
}