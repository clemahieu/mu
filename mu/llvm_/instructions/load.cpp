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

void mu::llvm_::instructions::load::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
	if (one.get () != nullptr)
	{
		auto one_ptr (boost::dynamic_pointer_cast <mu::llvm_::pointer_type::node> (one->type));
		if (one_ptr.get () != nullptr)
		{
			auto instruction (new llvm::LoadInst (one->value ()));
			context_a.results.push_back (boost::make_shared <mu::llvm_::instruction::node> (instruction, one_ptr->element));
		}
		else
		{
			std::wstringstream message;
			message << L"Argument is not a pointer";
			(*context_a.errors) (message.str ());
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::instructions::load::count ()
{
	return 1;
}