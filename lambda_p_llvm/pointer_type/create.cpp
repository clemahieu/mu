#include "create.h"

#include <core/errors/error_target.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/apint/node.h>
#include <lambda_p_llvm/pointer_type/node.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::pointer_type::create::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <lambda_p_llvm::pointer_type::node> (one));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::pointer_type::create::count ()
{
	return 1;
}