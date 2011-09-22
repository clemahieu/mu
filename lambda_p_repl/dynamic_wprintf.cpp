#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS

#include "dynamic_wprintf.h"

#include <lambda_p/core/statement.h>
#include <lambda_p_llvm/constant_wstring.h>
#include <lambda_p_llvm/value.h>
#include <lambda_p_llvm/generation_context.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Instructions.h>
#include <llvm/BasicBlock.h>

#include <sstream>

lambda_p_repl::dynamic_wprintf::dynamic_wprintf (::llvm::Value * wprintf_a, ::lambda_p_llvm::generation_context & context_a)
	: context (context_a),
	wprintf (wprintf_a)
{
}

lambda_p_repl::dynamic_wprintf::~dynamic_wprintf(void)
{
}

void lambda_p_repl::dynamic_wprintf::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	::std::wstring format;
	::std::vector < ::llvm::Value *> arguments;
	arguments.push_back (NULL); // Filled with format string after other arguments are computed
	for (size_t i = 1; i < argument_count; ++i)
	{
		::boost::shared_ptr < ::lambda_p::binder::node_instance> instance (instances [statement->arguments [i]]);
		::boost::shared_ptr < ::lambda_p_llvm::value> argument_value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (instance));
		if (argument_value.get () != NULL)
		{
			::llvm::Type const * type (argument_value->value_m->getType ());
			::llvm::PointerType const * pointer (::llvm::dyn_cast < ::llvm::PointerType> (type));
			if (pointer != NULL)
			{
				::llvm::Type const * element_type (pointer->getElementType ());
				::llvm::IntegerType const * element_integer (::llvm::dyn_cast < ::llvm::IntegerType> (element_type));
				if (element_integer != NULL)
				{
					if (element_integer->getBitWidth () == context.wchar_t_type->getBitWidth ())
					{
						format.append (L"%ls");
						arguments.push_back (argument_value->value_m);
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
				::llvm::IntegerType const * integer (::llvm::dyn_cast < ::llvm::IntegerType> (type));
				if (integer != NULL)
				{
					if (integer->getBitWidth () == 32)
					{
						format.append (L"%d");
						arguments.push_back (argument_value->value_m);
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
	::lambda_p_llvm::constant_wstring format_string (context, format);
	arguments [0] = format_string.value;
	::llvm::CallInst * call (::llvm::CallInst::Create (wprintf, arguments.begin (), arguments.end ()));
	context.block->getInstList ().push_back (call);
}

void lambda_p_repl::dynamic_wprintf::problem (size_t argument_position, ::std::wstringstream & problems)
{
	problems << L"Unknown argument type being passed to wprintf in position: ";
	problems << argument_position - 1;
	problems << '\n';
}