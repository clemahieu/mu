#include "create.h"

#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/value/node.h>

#include <llvm/Constants.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::null::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::pointer_type::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <lambda_p_llvm::value::node> (llvm::ConstantPointerNull::get (one->pointer_type ()), one));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::null::create::count ()
{
	return 1;
}