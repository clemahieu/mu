#include "load.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/instruction/node.h>
#include <lambda_p_llvm/pointer_type/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::instructions::load::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [0]));
	if (one.get () != nullptr)
	{
		auto one_ptr (boost::dynamic_pointer_cast <lambda_p_llvm::pointer_type::node> (one->type));
		if (one_ptr.get () != nullptr)
		{
			auto instruction (new llvm::LoadInst (one->value ()));
			results_a.push_back (boost::make_shared <lambda_p_llvm::instruction::node> (instruction, one_ptr->element));
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
		invalid_type (errors_a, parameters_a [0], 0);
	}
}

size_t lambda_p_llvm::instructions::load::count ()
{
	return 1;
}