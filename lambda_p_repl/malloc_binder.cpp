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
#include <lambda_p/core/declaration.h>
#include <lambda_p/core/association.h>
#include <lambda_p/errors/binder_string_error.h>

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


void lambda_p_repl::malloc_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	check_count_only_references (1, 1, statement, problems);
	if (problems.empty ())
	{
		::lambda_p::core::declaration * declaration (statement->association->results [0]);
		::lambda_p::core::node * size_node (statement->association->parameters [0]);
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
				instances [declaration] = value;
			}
			else
			{
				add_error (::std::wstring (L"malloc_binder expects argument 1 to be a size_t type"), problems);
			}
		}
		else
		{
			add_error (::std::wstring (L"malloc_binder expects argument 1 to be an llvm_value"), problems);
		}
	}
}

::std::wstring lambda_p_repl::malloc_binder::binder_name ()
{
	return ::std::wstring (L"malloc_binder");
}