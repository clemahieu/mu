//
//  load_binder.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/load_inst_binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/reference.h>
#include <lambda_p/core/declaration.h>

#include <llvm/Type.h>
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

#include <sstream>

lambda_p_llvm::load_inst_binder::load_inst_binder (::lambda_p_llvm::generation_context & context_a)
: context (context_a)
{
}

void lambda_p_llvm::load_inst_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	bool problem (false);
	check_count_only_references (problem, 1, 1, L"load_inst_binder", statement, problems);
	if (!problems)
	{
		::lambda_p::core::reference * pointer_node (static_cast < ::lambda_p::core::reference *> (statement->parameters [0]));
        ::boost::shared_ptr < ::lambda_p::binder::node_instance> pointer_instance (instances [pointer_node]);
        ::boost::shared_ptr < ::lambda_p_llvm::value> pointer (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (pointer_instance));
        if (pointer.get () != NULL)
        {
            if (pointer->value_m->getType ()->isPointerTy ())
            {
                ::llvm::LoadInst * load (new ::llvm::LoadInst (pointer->value_m));
                context.block->getInstList ().push_back (load);
                ::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::value (load));
				instances [statement->results [0]] = value;
            }
            else
            {
                problems << L"load_inst_binder expects argument 1 to be a pointer\n";
            }
        }
        else
        {
            problems << L"load_inst_binder expects argument 1 to be an llvm value\n";
        }
    }
}