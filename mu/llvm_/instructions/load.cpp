#include "load.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/pointer_type/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::instructions::load::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters_a, std::vector <boost::shared_ptr <mu::core::node>> & results_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (parameters_a [0]));
	if (one.get () != nullptr)
	{
		auto one_ptr (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (one->type));
		if (one_ptr.get () != nullptr)
		{
			auto instruction (new llvm::LoadInst (one->value ()));
			results_a.push_back (boost::make_shared <mu::llvm_::instruction::node> (instruction, one_ptr->element));
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

size_t mu::llvm_::instructions::load::count ()
{
	return 1;
}