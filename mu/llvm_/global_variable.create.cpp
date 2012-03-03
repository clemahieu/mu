#include <mu/llvm_/global_variable.create.h>

#include <mu/llvm_/type.node.h>
#include <mu/llvm_/global_variable.node.h>

#include <boost/make_shared.hpp>

#include <llvm/GlobalVariable.h>

void mu::llvm_::global_variable::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::type::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <mu::llvm_::global_variable::node> (new llvm::GlobalVariable (one->type (), false, llvm::GlobalValue::PrivateLinkage), one));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::global_variable::create::count ()
{
	return 1;
}
