#include "from_type.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/integer_type/node.h>

#include <sstream>

#include <llvm/DerivedTypes.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::integer_type::from_type::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	bool expected (check_size (errors_a, 1, parameters_a.size ()));
	if (expected)
	{
		auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (parameters_a [0]));
		if (type.get () != nullptr)
		{
			auto type_l (llvm::dyn_cast <llvm::IntegerType> (type->type ()));
			if (type_l != nullptr)
			{
				results_a.push_back (boost::make_shared <lambda_p_llvm::integer_type::node> (type_l));
			}
			else
			{
				(*errors_a) (L"Type is not an integer type");
			}
		}
		else
		{
			invalid_type (errors_a, 0);
		}
	}
}

std::wstring lambda_p_llvm::integer_type::from_type::name ()
{
	return std::wstring (L"lambda_p_llvm::integer_type::from_type");
}