//
//  memcpy_binder.cpp
//  lambda_p_llvm
//
//  Created by Colin LeMahieu on 9/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_llvm/memcpy_binder.h>

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>
#include <llvm/Function.h>

#include <sstream>

lambda_p_llvm::memcpy_binder::memcpy_binder (::lambda_p_llvm::generation_context & context_a, ::llvm::Function * memcpy_function_a)
: memcpy_function (memcpy_function_a),
context (context_a)
{
}

void lambda_p_llvm::memcpy_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
    size_t argument_count (statement->arguments.size ());
    if (argument_count == 4)
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
                        ::lambda_p::core::node * length_node (statement->arguments [3]);
                        ::lambda_p::core::node_id length_id (length_node->node_type());
                        switch (length_id)
                        {
                            case ::lambda_p::core::node_reference:
                            {
                                ::boost::shared_ptr < ::lambda_p::binder::node_instance> destination_instance (instances [destination_node]);
                                ::boost::shared_ptr < ::lambda_p_llvm::value> destination (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (destination_instance));
                                if (destination.get () != NULL)
                                {
                                    ::boost::shared_ptr < ::lambda_p::binder::node_instance> source_instance (instances [source_node]);
                                    ::boost::shared_ptr < ::lambda_p_llvm::value> source (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (source_instance));
                                    if (source.get () != NULL)
                                    {
                                        ::boost::shared_ptr < ::lambda_p::binder::node_instance> length_instance (instances [length_node]);
                                        ::boost::shared_ptr < ::lambda_p_llvm::value> length (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (length_instance));
                                        if (length.get () != NULL)
                                        {
                                            if (destination->value_m->getType () == ::llvm::Type::getInt8PtrTy (context.context))
                                            {
                                                if (source->value_m->getType () == ::llvm::Type::getInt8PtrTy (context.context))
                                                {
                                                    if (length->value_m->getType () == ::llvm::Type::getInt64Ty (context.context))
                                                    {
                                                        ::std::vector < ::llvm::Value *> arguments;
                                                        arguments.push_back (destination->value_m);
                                                        arguments.push_back (source->value_m);
                                                        arguments.push_back (length->value_m);
                                                        arguments.push_back (::llvm::ConstantInt::get (::llvm::Type::getInt32Ty (context.context), 0));
                                                        arguments.push_back (::llvm::ConstantInt::getFalse (context.context));
                                                        ::llvm::CallInst * call (::llvm::CallInst::Create (memcpy_function, arguments.begin (), arguments.end ()));
                                                        context.block->getInstList ().push_back (call);
                                                    }
                                                    else
                                                    {
                                                        problems << L"memcpy_binder expects length to be an Int64\n";
                                                    }
                                                }
                                                else
                                                {
                                                    problems << L"memcpy_binder expects source to be an Int8Ptr\n";
                                                }
                                            }
                                            else
                                            {
                                                problems << L"memcpy_binder expects destination to be an Int8Ptr\n";
                                            }
                                        }
                                    }
                                    else
                                    {
                                        problems << L"memcpy_binder expects destination to be an llvm value\n";
                                    }
                                }
                                else
                                {
                                    problems << L"memcpy_binder expects destination to be an llvm value\n";
                                }
                            }
                                break;
                            default:
                                problems << L"memcpy_binder expects argument 3 to be a reference, have: ";
                                problems << length_node->node_type_name ();
                                problems << '\n';
                                break;
                        }
                    }
                        break;
                    default:
                        problems << L"memcpy_binder expects argument 2 to be a reference, have: ";
                        problems << source_node->node_type_name ();
                        problems << '\n';
                        break;
                }
            }
                break;
            default:
                problems << L"memcpy_binder expects argument 1 to be a reference, have: ";
                problems << destination_node->node_type_name ();
                problems << '\n';
                break;
        }
    }
    else
    {
        problems << L"memcpy_binder is expecting 3 arguments, have: ";
        problems << argument_count - 1;
        problems << '\n';
    }
}