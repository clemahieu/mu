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
#include <lambda_p/core/node.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/reference.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

#include <sstream>

lambda_p_llvm::store_inst_binder::store_inst_binder (::lambda_p_llvm::generation_context & context_a)
: context (context_a)
{
}

void lambda_p_llvm::store_inst_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	bool problem (false);
	check_count_only_references (problem, 0, 2, L"store_inst_binder", statement, problems);
	if (!problem)
	{
		::lambda_p::core::reference * destination_node (static_cast < ::lambda_p::core::reference *> (statement->parameters [0]));
		::lambda_p::core::reference * source_node (static_cast < ::lambda_p::core::reference *> (statement->parameters [1]));
		::boost::shared_ptr < ::lambda_p::binder::node_instance> source_instance (instances [source_node]);
		::boost::shared_ptr < ::lambda_p_llvm::value> source (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (source_instance));
		if (source.get () != NULL)
		{
			::boost::shared_ptr < ::lambda_p::binder::node_instance> destination_instance (instances [destination_node]);
			::boost::shared_ptr < ::lambda_p_llvm::value> destination (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (destination_instance));
			if (destination.get () != NULL)
			{
				::llvm::PointerType const * destination_pointer (::llvm::dyn_cast < ::llvm::PointerType const> (destination->value_m->getType ()));
				if (destination_pointer != NULL)
				{
					if (destination_pointer->getElementType () == source->value_m->getType ())
					{
						::llvm::StoreInst * store (new ::llvm::StoreInst (source->value_m, destination->value_m));
						context.block->getInstList ().push_back (store);
					}
					else
					{
						problems << L"store_inst_binder expects argument 1 to be a pointer to the type of argument 2\n";
					}
				}
				else
				{
					problems << L"store_inst_binder expects argument 1 to be a pointer\n";
				}
			}
			else
			{
				problems << L"store_inst_binder expects argument 1 to be an llvm value\n";
			}
		}
		else
		{
			problems << L"store_inst_binder expects argument 2 to be an llvm value\n";
		}
	}
}