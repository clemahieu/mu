#include "get_type.h"

#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/type/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Value.h>

void lambda_p_llvm::value::get_type::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		results.push_back (boost::make_shared <lambda_p_llvm::type::node> (one->value ()->getType ()));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::value::get_type::count ()
{
	return 1;
}