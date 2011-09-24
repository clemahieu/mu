//
//  malloc_binder.cpp
//  lambda_p_repl
//
//  Created by Colin LeMahieu on 9/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include <lambda_p_repl/malloc_binder.h>

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/Instructions.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/BasicBlock.h>

#include <sstream>

lambda_p_repl::malloc_binder::malloc_binder (::lambda_p_llvm::generation_context & context_a, ::llvm::Function * malloc_a)
: malloc (malloc_a),
context (context_a)
{
}


void lambda_p_repl::malloc_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
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
                ::lambda_p::core::node * size_node (statement->arguments [2]);
                ::lambda_p::core::node_id size_id (size_node->node_type ());
                switch (size_id)
                {
                    case ::lambda_p::core::node_reference:
                    {
                        ::boost::shared_ptr < ::lambda_p::binder::node_instance> size_instance (instances [size_node]);
                        ::boost::shared_ptr < ::lambda_p_llvm::value> size_value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (size_instance));
                        if (size_value.get () != NULL)
                        {
                            ::llvm::Type const * size_type (size_value->value_m->getType ());
                            ::llvm::Type const * size_t_type (context.size_t_type);
                            if (size_type == size_t_type)
                            {
                                ::std::vector < ::llvm::Value *> arguments;
                                arguments.push_back (size_value->value_m);
                                ::llvm::CallInst * call (::llvm::CallInst::Create (malloc, arguments.begin (), arguments.end ()));
                                context.block->getInstList ().push_back (call);
                                ::boost::shared_ptr < ::lambda_p_llvm::value> value (new ::lambda_p_llvm::value (call));
                                instances [declaration_node] = value;
                            }
                            else
                            {
                                problems << L"malloc_binder expects argument 2 to be a size_t type\n";
                            }
                        }
                        else
                        {
                            problems << L"malloc_binder expects argument 2 to be an llvm_value\n";
                        }
                    }
                        break;
                    default:
                        problems << L"malloc_binder expects argument 2 to be a reference, have: ";
                        problems << size_node->node_type_name ();
                        problems << '\n';
                        break;
                }
            }
                break;
            default:
                problems << L"malloc_binder expects argument 1 to be a declaration, have: ";
                problems << declaration_node->node_type_name ();
                problems << '\n';
                break;
        }
    }
    else
    {
        problems << L"malloc_binder is expecting 2 arguments, have: ";
        problems << argument_count - 1;
        problems << '\n';
    }
}