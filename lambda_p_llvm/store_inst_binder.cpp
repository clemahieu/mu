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
    size_t argument_count (statement->arguments.size ());
    if (argument_count == 3)
    {
        ::lambda_p::core::node * destination_node (statement->arguments [1]);
        ::lambda_p::core::node_id destination_id (destination_node->node_type ());
        switch (destination_id)
        {
            case ::lambda_p::core::node_reference:
            {
                ::lambda_p::core::node * source_node (statement->arguments [2]);
                ::lambda_p::core::node_id source_id (source_node->node_type ());
                switch (source_id)
                {
                    case ::lambda_p::core::node_reference:
                    {
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
                        break;
                    default:
                        problems << L"store_inst_binder expects argument 2 to be a reference, have: ";
                        problems << source_node->node_type_name ();
                        problems << '\n';
                        break;
                }
            }
                break;
            default:
                problems << L"store_inst_binder expects argument 1 to be a reference, have: ";
                problems << destination_node->node_type_name ();
                problems << '\n';
                break;
        }
    }
    else
    {
        problems << L"store_inst_binder is expecting 2 arguments, have: ";
        problems << argument_count - 1;
        problems << '\n';
    }
}