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
	if (statement->association->declarations.size () == 1)
	{
		llvm::FunctionType const * function_type (llvm::dyn_cast <llvm::FunctionType> (type));
		if (function_type != nullptr)
		{
			size_t formal_argument_count (function_type->getNumParams ());
			if (formal_argument_count == statement->association->references.size ())
			{
				for (auto i (0); i < formal_argument_count; ++i)
				{
					auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type_inference> (nodes [statement->association->references [i]]));
					check_binder (type, i, L"type", problems);
					if (problems.errors.empty ())
					{
						llvm::Type const * formal (function_type->getParamType (i));
						llvm::IntegerType const * int_type (llvm::dyn_cast <llvm::IntegerType> (type->type));
						if (formal != type->type)
						{
							std::wstringstream message;
							message << L"Formal argument: ";
							std::string desc (formal->getDescription ());
							message << std::wstring (desc.begin (), desc.end ());
							message << L" does not match actual argument: ";
							std::string description (type->type->getDescription ());
							message << std::wstring (description.begin (), description.end ());
							add_error (message.str (), problems);
						}
						else
						{
						}
					}
				}
				if (problems.errors.empty ())
				{
					nodes [statement->association->declarations [0]] = boost::shared_ptr <lambda_p_llvm::type_inference> (new lambda_p_llvm::type_inference (function_type->getReturnType ()));
				}
			}
			else
			{
				std::wstringstream message;
				message << L"Number of parameters in function: ";
				message << formal_argument_count;
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
	else
	{
		add_error (std::wstring (L"type_inference must have exactly one declaration"), problems);
	}
}

std::wstring lambda_p_llvm::type_inference::binder_name ()
{
	return std::wstring (L"type_inference");
}