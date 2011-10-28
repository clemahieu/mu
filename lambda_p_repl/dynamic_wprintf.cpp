#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "dynamic_wprintf.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_llvm/constant_wstring.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/core/association.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/binder/routine_instances.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

#include <sstream>

lambda_p_repl::dynamic_wprintf::dynamic_wprintf (llvm::Value * wprintf_a, lambda_p_llvm::generation_context & context_a)
	: context (context_a),
	wprintf (wprintf_a)
{
}

lambda_p_repl::dynamic_wprintf::~dynamic_wprintf(void)
{
}

void lambda_p_repl::dynamic_wprintf::bind (lambda_p::core::statement * statement, lambda_p::binder::routine_instances & instances, lambda_p::errors::error_list & problems)
{
	size_t parameter_count (statement->association->parameters.size ());
	std::wstring format;
	std::vector <llvm::Value *> arguments;
	arguments.push_back (NULL); // Filled with format string after other arguments are computed
	for (size_t i = 0; i < parameter_count; ++i)
	{
		boost::shared_ptr <lambda_p::binder::node> instance (instances [statement->association->parameters [i]]);
		boost::shared_ptr <lambda_p_llvm::value> argument_value (boost::dynamic_pointer_cast < lambda_p_llvm::value> (instance));
		if (argument_value.get () != NULL)
		{
			llvm::Type const * type (argument_value->type ());
			llvm::PointerType const * pointer (llvm::dyn_cast < llvm::PointerType> (type));
			if (pointer != NULL)
			{
				llvm::Type const * element_type (pointer->getElementType ());
				llvm::IntegerType const * element_integer (llvm::dyn_cast < llvm::IntegerType> (element_type));
				if (element_integer != NULL)
				{
					if (element_integer->getBitWidth () == context.wchar_t_type->getBitWidth ())
					{
						format.append (L"%ls");
						arguments.push_back (argument_value->operator() ());
					}
					else
					{
						problem (i, problems);
					}
				}
				else
				{
					problem (i, problems);
				}
			}
			else
			{
				llvm::IntegerType const * integer (llvm::dyn_cast < llvm::IntegerType> (type));
				if (integer != NULL)
				{
					if (integer->getBitWidth () == 64)
					{
						format.append (L"%lu");
						arguments.push_back (argument_value->operator() ());
					}
					else
					{
						problem (i, problems);
					}
				}
				else
				{					
					problem (i, problems);
				}
			}
		}
		else
		{
			problem (i, problems);
		}
	}
	lambda_p_llvm::constant_wstring format_string (context, format);
	arguments [0] = format_string.value;
	llvm::CallInst * call (llvm::CallInst::Create (wprintf, arguments.begin (), arguments.end ()));
	context.block->getInstList ().push_back (call);
}

void lambda_p_repl::dynamic_wprintf::problem (size_t argument_position, lambda_p::errors::error_list & problems)
{
	std::wstring message;
	message.append (L"Unknown argument type being passed to wprintf in position: ");
	std::wstringstream stream;
	stream << argument_position;
	message.append (stream.str ());
	add_error (message, problems);
}

std::wstring lambda_p_repl::dynamic_wprintf::binder_name ()
{
	return std::wstring (L"dynamic_wprintf_binder");
}