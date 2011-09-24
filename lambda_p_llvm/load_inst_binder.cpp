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
    size_t argument_count (statement->arguments.size ());
    if (argument_count == 3)
    {
        ::lambda_p::core::node * declaration_node (statement->arguments [1]);
        ::lambda_p::core::node_id declaration_id (declaration_node->node_type ());
        switch (declaration_id)
        {
            case ::lambda_p::core::node_declaration:
            {
                ::lambda_p::core::node * pointer_node (statement->arguments [2]);
                ::lambda_p::core::node_id pointer_id (pointer_node->node_type ());
                switch (pointer_id)
                {
                    case ::lambda_p::core::node_reference:
                    {
                        ::boost::shared_ptr < ::lambda_p::binder::node_instance> pointer_instance (instances [pointer_node]);
                        ::boost::shared_ptr < ::lambda_p_llvm::value> pointer (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (pointer_instance));
                        if (pointer.get () != NULL)
                        {
                            if (pointer->value_m->getType ()->isPointerTy ())
                            {
                                ::llvm::LoadInst * load (new ::llvm::LoadInst (pointer->value_m));
                                context.block->getInstList ().push_back (load);
                                ::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::value (load));
                                instances [declaration_node] = value;
                            }
                            else
                            {
                                problems << L"load_inst_binder expects argument 2 to be a pointer\n";
                            }
                        }
                        else
                        {
                            problems << L"load_inst_binder expects argument 2 to be an llvm value\n";
                        }
                    }
                        break;
                    default:
                        problems << L"load_inst_binder expects argument 2 to be a reference, have: ";
                        problems << pointer_node->node_type_name ();
                        problems << '\n';
                        break;
                }
            }
                break;
            default:
                problems << L"load_inst_binder expects argument 1 to be a declaration, have: ";
                problems << declaration_node->node_type_name ();
                problems << '\n';
                break;
        }
    }
    else
    {
        problems << L"load_inst_binder is expecting 2 arguments, have: ";
        problems << argument_count - 1;
        problems << '\n';
    }
}