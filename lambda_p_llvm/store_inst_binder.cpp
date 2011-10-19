//
//  store_binder.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/store_inst_binder.h>

#include <lambda_p/core/statement.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

#include <sstream>

lambda_p_llvm::store_inst_binder::store_inst_binder (lambda_p_llvm::generation_context & context_a)
: context (context_a)
{
}

void lambda_p_llvm::store_inst_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems)
{
	check_count (0, 2, statement, problems);
	if (problems.empty ())
	{
		size_t destination_node (statement->association->parameters [0]);
		size_t source_node (statement->association->parameters [1]);
		boost::shared_ptr < lambda_p::binder::instance> source_instance (instances [source_node]);
		boost::shared_ptr < lambda_p_llvm::value> source (boost::dynamic_pointer_cast < lambda_p_llvm::value> (source_instance));
		if (source.get () != NULL)
		{
			boost::shared_ptr < lambda_p::binder::instance> destination_instance (instances [destination_node]);
			boost::shared_ptr < lambda_p_llvm::value> destination (boost::dynamic_pointer_cast < lambda_p_llvm::value> (destination_instance));
			if (destination.get () != NULL)
			{
				llvm::PointerType const * destination_pointer (llvm::dyn_cast < llvm::PointerType const> (destination->type ()));
				if (destination_pointer != NULL)
				{
					if (destination_pointer->getElementType () == source->type ())
					{
						llvm::StoreInst * store (new llvm::StoreInst (source->operator () (), destination->operator () ()));
						context.block->getInstList ().push_back (store);
					}
					else
					{
						add_error (std::wstring (L"store_inst_binder expects argument 1 to be a pointer to the type of argument 2"), problems);
					}
				}
				else
				{
					add_error (std::wstring (L"store_inst_binder expects argument 1 to be a pointer"), problems);
				}
			}
			else
			{
				add_error (std::wstring (L"store_inst_binder expects argument 1 to be an llvm value"), problems);
			}
		}
		else
		{
			add_error (std::wstring (L"store_inst_binder expects argument 2 to be an llvm value"), problems);
		}
	}
}

std::wstring lambda_p_llvm::store_inst_binder::binder_name ()
{
	return std::wstring (L"store_inst_binder");
}