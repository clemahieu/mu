#include "store.h"

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/void_type/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void mu::llvm_::instructions::store::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::llvm_::value::node, mu::llvm_::value::node> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters [1]));
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
}