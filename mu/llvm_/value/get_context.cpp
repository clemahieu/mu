#include "get_context.h"

#include <mu/llvm_/value/node.h>
#include <mu/llvm_/context/node.h>

#include <llvm/Value.h>

#include <boost/make_shared.hpp>

void mu::llvm_::value::get_context::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <mu::llvm_::context::node> (&one->value ()->getContext ()));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::llvm_::value::get_context::count ()
{
	return 1;
}