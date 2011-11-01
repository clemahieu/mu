#include "function_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_llvm/fo_value.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/errors/error_list.h>

#include <llvm/Function.h>
#include <llvm/Instructions.h>

#include <sstream>

lambda_p_llvm::function_binder::function_binder (lambda_p_llvm::generation_context & context_a, llvm::Function * function_a)
	: function (function_a),
	context (context_a)
{
}

void lambda_p_llvm::function_binder::bind (lambda_p::core::statement * statement, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	if (statement->association->declarations.size () == 1)
	{
		if (statement->association->references.size () == function->arg_size ())
		{
			std::vector <llvm::Value *> arguments;
			size_t position (0);
			for (auto i = statement->association->references.begin (); i != statement->association->references.end (); ++i, ++position)
			{
				boost::shared_ptr <lambda_p_llvm::fo_value> value (boost::dynamic_pointer_cast <lambda_p_llvm::fo_value> (nodes [*i]));
				if (value.get () != nullptr)
				{
					arguments.push_back (value->value);
				}
				else
				{
					unexpected_binder_type_error (position, L"fo_value", problems);
				}
			}
			if (problems.errors.empty ())
			{				
				llvm::CallInst * call (llvm::CallInst::Create (function, arguments.begin (), arguments.end ()));
				context.block->getInstList ().push_back (call);
				boost::shared_ptr <lambda_p_llvm::fo_value> value (new lambda_p_llvm::fo_value (call));
				nodes [statement->association->declarations [0]] = value;
			}
		}
		else
		{
			std::wstringstream message;
			message << L"Number of arguments: ";
			message << statement->association->references.size ();
			message << L" does not match number of parameters: ";
			message << function->arg_size ();
			add_error (message.str (), problems);
		}
	}
	else
	{
		add_error (L"expected 1 result", problems);
	}
}

std::wstring lambda_p_llvm::function_binder::binder_name ()
{
	return std::wstring (L"function_binder");
}
