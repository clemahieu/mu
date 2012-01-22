#include "operation.h"

#include <lambda_p/routine.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/function/node.h>

#include <llvm/Function.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>

#include <sstream>

lambda_p_llvm::function::operation::operation (boost::shared_ptr <lambda_p_llvm::function::node> function_a)
	: function (function_a)
{
}

void lambda_p_llvm::function::operation::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> arguments_a, std::vector <boost::shared_ptr <lambda_p_llvm::value::node>> & results_a)
{
	assert (results_a.empty ());
	if (arguments_a.size () == function->function ()->getFunctionType ()->getNumParams ())
	{
		bool good (true);
		std::vector <llvm::Value *> arguments;
		for (size_t i (0), j (arguments_a.size ()); i != j && good; ++i)
		{
			auto argument_type (function->function ()->getFunctionType ()->getParamType (i));
			auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (arguments_a [i]));
			if (value.get () != nullptr)
			{
				arguments.push_back (value->value ());
				if (value->value ()->getType () != argument_type)
				{
					std::wstringstream message;
					message << L"Invalid type at position: ";
					message << i;
					(*errors_a) (message.str ());
					good = false;
				}
			}
			else
			{
				//auto routine (boost::dynamic_pointer_cast <lambda_p::routine> (arguments_a [i]));
				//if (routine.get () != nullptr)
				//{
				//}
				//else
				//{
					std::wstringstream message;
					message << L"Parameter at position: ";
					message << i;
					message << L" is not a value";
					(*errors_a) (message.str ());
					good = false;
				//}
			}
		}
		if (good)
		{
			auto call (llvm::CallInst::Create (function->function (), arguments));
			context_a->getInstList ().push_back (call);
			if (function->multiple_return)
			{
				auto return_type (llvm::cast <llvm::StructType> (function->function ()->getReturnType ()));
				for (size_t i (0), j (return_type->getNumElements()); i != j; ++i)
				{
					auto element (llvm::ExtractValueInst::Create (call, i));
					context_a->getInstList ().push_back (element);
					results_a.push_back (boost::shared_ptr <lambda_p_llvm::value::node> (new lambda_p_llvm::value::node (element)));
				}
			}
			else
			{
				if (!call->getType ()->isVoidTy ())
				{
					results_a.push_back (boost::shared_ptr <lambda_p_llvm::value::node> (new lambda_p_llvm::value::node (call)));
				}
			}
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Actual number of arguments: ";
		message << arguments_a.size ();
		message << L" doesn't match number of formal parameters: ";
		message << function->function ()->getFunctionType ()->getNumParams ();
		(*errors_a) (message.str ());
	}
}