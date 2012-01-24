#include "create_int.h"

#include <lambda_p_script/integer/node.h>
#include <lambda_p_llvm/execution_engine/generic_value/node.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::execution_engine::generic_value::create_int::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::integer::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto result (boost::make_shared <lambda_p_llvm::execution_engine::generic_value::node> ());
			result->value.IntVal = llvm::APInt ((unsigned int) (one->value), (uint64_t) (two->value));
			results.push_back (result);
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t lambda_p_llvm::execution_engine::generic_value::create_int::count ()
{
	return 2;
}