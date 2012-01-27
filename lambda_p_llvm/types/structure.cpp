#include "structure.h"

#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/pointer_type/node.h>
#include <lambda_p_llvm/struct_type/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/ADT/ArrayRef.h>

#include <boost/make_shared.hpp>

void lambda_p_llvm::types::structure::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	std::vector <llvm::Type *> types;
	bool good (true);
	size_t position (0);
	for (auto i (parameters_a.begin ()), j (parameters_a.end ()); i != j && good; ++i, ++position)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (parameters_a [0]));
		if (one.get () != nullptr)
		{
			types.push_back (one->type ());
		}
		else
		{
			good = false;
			invalid_type (errors_a, position);
		}
	}
	if (good)
	{
		results_a.push_back (boost::make_shared <lambda_p_llvm::struct_type::node> (llvm::StructType::get (context_a->getContext (), types, false)));
	}
}