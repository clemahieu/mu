#include "store.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/void_type/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::instructions::store::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::llvm_::value::node> (context_a.parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			auto ptr (llvm::dyn_cast <llvm::PointerType> (two->value ()->getType ()));
			if (ptr != nullptr)
			{
				if (ptr->getElementType () == one->value ()->getType ())
				{
					auto instruction (new llvm::StoreInst (one->value (), two->value ()));
					context_a.results.push_back (boost::make_shared <mu::llvm_::instruction::node> (instruction, boost::make_shared <mu::llvm_::void_type::node> (boost::make_shared <mu::llvm_::context::node> (&instruction->getContext ()))));
				}
				else
				{
					std::wstringstream message;
					message << L"Argument two is not a pointer to the type of argument one";
					(*context_a.errors) (message.str ());
				}
			}
			else
			{
				std::wstringstream message;
				message << L"Argument 2 is not a pointer";
				(*context_a.errors) (message.str ());
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::llvm_::instructions::store::count ()
{
	return 2;
}