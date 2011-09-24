//
//  cast_inst_binder.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/cast_inst_binder.h>

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/type.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

#include <sstream>

lambda_p_llvm::cast_inst_binder::cast_inst_binder (::lambda_p_llvm::generation_context & context_a)
: context (context_a)
{
}

void lambda_p_llvm::cast_inst_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
    size_t argument_count (statement->arguments.size ());
    if (argument_count == 4)
    {
        ::lambda_p::core::node * declaration_node (statement->arguments [1]);
        ::lambda_p::core::node_id declaration_id (declaration_node->node_type ());
        switch (declaration_id)
        {
            case ::lambda_p::core::node_declaration:
            {
                ::lambda_p::core::node * value_node (statement->arguments [2]);
                ::lambda_p::core::node_id value_id (value_node->node_type ());
                switch (value_id)
                {
                    case ::lambda_p::core::node_reference:
                    {
                        ::lambda_p::core::node * type_node (statement->arguments [3]);
                        ::lambda_p::core::node_id type_id (type_node->node_type ());
                        switch (type_id)
                        {
                            case ::lambda_p::core::node_reference:
                            {
                                ::boost::shared_ptr < ::lambda_p::binder::node_instance> value_instance (instances [value_node]);
                                ::boost::shared_ptr < ::lambda_p_llvm::value> value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (value_instance));
                                if (value.get () != NULL)
                                {
                                    ::boost::shared_ptr < ::lambda_p::binder::node_instance> type_instance (instances [type_node]);
                                    ::boost::shared_ptr < ::lambda_p_llvm::type> type (::boost::dynamic_pointer_cast < ::lambda_p_llvm::type> (type_instance));
                                    if (type.get () != NULL)
                                    {
                                        ::llvm::CastInst * cast (::llvm::CastInst::CreatePointerCast (value->value_m, type->type_m));
                                        context.block->getInstList ().push_back (cast);
                                        ::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::value (cast));
                                        instances [declaration_node] = value;
                                    }
                                    else 
                                    {
                                        problems << L"cast_inst_binder is expecting argument 3 to be an llvm type\n";
                                    }
                                }
                                else
                                {
                                    problems << L"cast_inst_binder is expecting argument 2 to be an llvm value\n";
                                }
                            }
                                break;
                            default:
                                problems << L"cast_inst_binder is expecting argument 3 to be a reference, have: ";
                                problems << type_node->node_type_name ();
                                problems << '\n';
                        }
                    }
                        break;
                    default:
                        problems << L"cast_inst_binder is expecting argument 2 to be a reference, have: ";
                        problems << value_node->node_type_name ();
                        problems << '\n';
                }
            }
                break;
            default:
                problems << L"cast_inst_binder is expecting argument 1 to be a declaration, have: ";
                problems << declaration_node->node_type_name ();
                problems << '\n';
                break;
        }
    }
    else
    {
        problems << L"cast_inst_binder is expecting 3 arguments, have: ";
        problems << argument_count - 1;
        problems << '\n';
    }
}