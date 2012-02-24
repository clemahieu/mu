#include "get_type.h"

#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/type/build.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/context/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Value.h>

void lambda_p_llvm::value::get_type::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [0]));
	if (one.get () != nullptr)
	{
		lambda_p_llvm::type::build build (boost::make_shared <lambda_p_llvm::context::node> (&one->value ()->getContext ()), one->value ()->getType ());
		results_a.push_back (build.type);
	}
	else
	{
		invalid_type (errors_a, parameters_a [0], 0);
	}
}

size_t lambda_p_llvm::value::get_type::count ()
{
	return 1;
}