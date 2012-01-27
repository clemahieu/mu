#include "cmpxchg.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/value/node.h>

#include <llvm/Value.h>
#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::instructions::cmpxchg::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	if (check_size (errors_a, 3, parameters_a.size ()))
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [0]));
		auto two (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [1]));
		auto three (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters_a [1]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				if (three.get () != nullptr)
				{
					auto ptr (llvm::dyn_cast <llvm::PointerType> (one->value ()->getType ()));
					if (ptr != nullptr)
					{
						auto two_type (ptr->getElementType () == two->value ()->getType ());
						auto three_type (ptr->getElementType () == two->value ()->getType ());;
						if (two_type && three_type)
						{
							auto instruction (new llvm::AtomicCmpXchgInst (one->value (), two->value (), three->value (), llvm::AtomicOrdering::Monotonic, llvm::SynchronizationScope::CrossThread));
							context_a->getInstList ().push_back (instruction);
							results_a.push_back (boost::make_shared <lambda_p_llvm::value::node> (instruction));
						}
						else
						{
							std::wstringstream message;
							message << L"Argument one is not a pointer to the type of argument two and three: ";
							message << two_type;
							message << L" ";
							message << three_type;
							(*errors_a) (message.str ());
						}
					}
					else
					{
						std::wstringstream message;
						message << L"Argument 1 is not a pointer";
						(*errors_a) (message.str ());
					}
				}
				else
				{
					invalid_type (errors_a, 2);
				}
			}
			else
			{
				invalid_type (errors_a, 1);
			}
		}
		else
		{
			invalid_type (errors_a, 0);
		}
	}
}