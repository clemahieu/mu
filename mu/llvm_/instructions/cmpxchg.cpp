#include <mu/llvm_/instructions/cmpxchg.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/instruction/node.h>
#include <mu/script/check.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

bool mu::llvm_::instructions::cmpxchg::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::llvm_::value::node, mu::llvm_::value::node, mu::llvm_::value::node> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters (0)));
		auto two (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters (1)));
		auto three (boost::static_pointer_cast <mu::llvm_::value::node> (context_a.parameters (1)));
		auto ptr (llvm::dyn_cast <llvm::PointerType> (one->value ()->getType ()));
		if (ptr != nullptr)
		{
			auto two_type (ptr->getElementType () == two->value ()->getType ());
			auto three_type (ptr->getElementType () == two->value ()->getType ());;
			if (two_type && three_type)
			{
				auto instruction (new llvm::AtomicCmpXchgInst (one->value (), two->value (), three->value (), llvm::AtomicOrdering::Monotonic, llvm::SynchronizationScope::CrossThread));
				context_a.push (boost::make_shared <mu::llvm_::value::node> (instruction, two->type));
			}
			else
			{
				std::wstringstream message;
				message << L"Argument one is not a pointer to the type of argument two and three: ";
				message << two_type;
				message << L" ";
				message << three_type;
				context_a.errors (message.str ());
				result = false;
			}
		}
		else
		{
			std::wstringstream message;
			message << L"Argument 1 is not a pointer";
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}