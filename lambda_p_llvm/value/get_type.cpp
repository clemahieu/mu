#include "get_type.h"

#include <lambda_p_llvm/value/node.h>
#include <lambda_p_llvm/type/node.h>

#include <boost/make_shared.hpp>

#include <llvm/Value.h>

void lambda_p_llvm::value::get_type::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	auto expected (check_size (errors_a, 1, parameters_a.size ()));
	if (expected)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [0]));
		if (one.get () != nullptr)
		{
			results_a.push_back (boost::make_shared <lambda_p_llvm::type::node> (one->value ()->getType ()));
		}
		else
		{
			invalid_type (errors_a, 0);
		}
	}
}