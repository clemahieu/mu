#include "function_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/Function.h>
#include <llvm/Instructions.h>

#include <sstream>

lambda_p_llvm::function_binder::function_binder (lambda_p_llvm::generation_context & context_a, llvm::Function * function_a)
	: function (function_a),
	context (context_a)
{
}

void lambda_p_llvm::function_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, std::vector < boost::shared_ptr < lambda_p::errors::error> > & problems)
{
	if (statement->association->results.size () == 1)
	{
		if (statement->association->parameters.size () == function->arg_size ())
		{
			std::vector < llvm::Value *> arguments;
			size_t position (0);
			for (std::vector <size_t>::iterator i = statement->association->parameters.begin (); i != statement->association->parameters.end (); ++i, ++position)
			{
				boost::shared_ptr < lambda_p_llvm::fo_value> value (boost::dynamic_pointer_cast < lambda_p_llvm::fo_value> (instances [*i]));
				if (value.get () != NULL)
				{
					arguments.push_back (value->value);
				}
				else
				{
					unexpected_binder_type_error (position, std::wstring (L"fo_value"), problems);
				}
			}
			if (problems.empty ())
			{				
				llvm::CallInst * call (llvm::CallInst::Create (function, arguments.begin (), arguments.end ()));
				context.block->getInstList ().push_back (call);
				boost::shared_ptr < lambda_p_llvm::fo_value> value (new lambda_p_llvm::fo_value (call));
				instances [statement->association->results [0]] = value;
			}
		}
		else
		{
			std::wstringstream message;
			message << L"Number of arguments: ";
			message << statement->association->parameters.size ();
			message << L" does not match number of parameters: ";
			message << function->arg_size ();
			add_error (message.str (), problems);
		}
	}
	else
	{
		add_error (std::wstring (L"expected 1 result"), problems);
	}
}

std::wstring lambda_p_llvm::function_binder::binder_name ()
{
	return std::wstring (L"function_binder");
}
