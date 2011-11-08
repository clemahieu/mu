#include "type_inference.h"

#include <lambda_p/binder/binder_implementor.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

lambda_p_llvm::type_inference::type_inference (llvm::Type const * type_a)
	: type (type_a)
{
}

void lambda_p_llvm::type_inference::bind (lambda_p::core::statement * statement, lambda_p::binder::list & nodes, lambda_p::errors::error_list & problems)
{
	llvm::FunctionType const * function_type (llvm::dyn_cast <llvm::FunctionType> (type));
	if (function_type != nullptr)
	{
		if (function_type->getNumParams () == statement->association->references.size ())
		{

		}
		else
		{
			std::wstringstream message;
			message << L"Number of parameters in function: ";
			message << function_type->getNumParams ();
			message << L" does not match number of arguments: ";
			message << statement->association->references.size ();
			add_error (message.str (), problems);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Cannot use type: ";
		std::string description (type->getDescription ());
		message << std::wstring (description.begin (), description.end ());
		message << L" as target of invocation";
		add_error (message.str (), problems);
	}
}

std::wstring lambda_p_llvm::type_inference::binder_name ()
{
	return std::wstring (L"type_inference");
}