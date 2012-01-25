#include "load.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/value/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::instructions::load::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	if (check_size (errors_a, 1, parameters_a.size ()))
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [0]));
		if (one.get () != nullptr)
		{
			bool one_ptr (one->value ()->getType ()->isPointerTy ());
			if (one_ptr)
			{
				auto instruction (new llvm::LoadInst (one->value ()));
				context_a->getInstList ().push_back (instruction);
				results_a.push_back (boost::make_shared <lambda_p_llvm::value::node> (instruction));
			}
			else
			{
				std::wstringstream message;
				message << L"Argument is not a pointer";
				(*errors_a) (message.str ());
			}
		}
		else
		{
			invalid_type (errors_a, 0);
		}
	}
}