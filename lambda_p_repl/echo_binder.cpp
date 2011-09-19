#define __STDC_LIMIT_MACROS

#include "echo_binder.h"

#include <lambda_p/core/statement.h>
#include <lambda_p/core/node.h>
#include <lambda_p/core/data.h>
#include <lambda_p/binder/command_list.h>
#include <lambda_p_llvm/llvm_value.h>
#include <lambda_p_llvm/llvm_generation_context.h>

#include <llvm/Constants.h>
#include <llvm/DerivedTypes.h>
#include <llvm/GlobalValue.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Module.h>
#include <llvm/Instructions.h>

#include <sstream>

lambda_p_repl::echo_binder::echo_binder (::llvm::Value * wprintf_a, ::lambda_p_llvm::llvm_generation_context context_a)
	: context (context_a),
wprintf (wprintf_a)
{
    ::std::vector < ::llvm::Constant *> echo_string_initializer;
    echo_string_initializer.push_back (::llvm::ConstantInt::get (context.wchar_t_type, '%'));
    echo_string_initializer.push_back (::llvm::ConstantInt::get (context.wchar_t_type, 's'));
    echo_string_initializer.push_back (::llvm::ConstantInt::get (context.wchar_t_type, '\0'));
    ::llvm::ArrayType * echo_string_type (::llvm::ArrayType::get (context.wchar_t_type, 3));
    ::llvm::Constant * echo_string (::llvm::ConstantArray::get (echo_string_type, echo_string_initializer));
    echo_string_global = new ::llvm::GlobalVariable (echo_string_type, true, ::llvm::GlobalValue::ExternalLinkage, echo_string);
    context.module->getGlobalList ().push_back (echo_string_global);
}

lambda_p_repl::echo_binder::~echo_binder(void)
{
}

void lambda_p_repl::echo_binder::bind (::lambda_p::core::statement * statement, ::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> > & instances, ::std::wstringstream & problems)
{
	size_t argument_count (statement->arguments.size ());
	if (argument_count == 2)
	{
		::lambda_p::core::node_id node_id (statement->arguments [1]->node_type ());
		switch (node_id)
		{
		case ::lambda_p::core::node_reference:
			{
				::std::map < ::lambda_p::core::node *, ::boost::shared_ptr < ::lambda_p::binder::node_instance> >::iterator search (instances.find (statement->arguments [1]));
				assert (search != instances.end ());
				::boost::shared_ptr < ::lambda_p::binder::node_instance> instance (search->second);
				::boost::shared_ptr < ::lambda_p_llvm::llvm_value> string (::boost::dynamic_pointer_cast < ::lambda_p_llvm::llvm_value> (instance));
				if (string.get () != NULL)
				{
                    ::std::vector < ::llvm::Value *> arguments;
                    arguments.push_back (echo_string_global);
                    arguments.push_back (string->value);
                    ::llvm::CallInst * call (::llvm::CallInst::Create (wprintf, arguments.begin (), arguments.end ()));
                    context.block->getInstList ().push_back (call);
				}
				else
				{
					problems << L"Argument 1 is not an llvm_value\n";
				}
			}
			break;
		default:
			problems << L"echo is expecting argument 1 to be data, have: ";
			problems << statement->arguments [1]->node_type_name ();
			problems << '\n';
			break;
		}
	}
	else
	{
		problems << L"echo is expecting one argument, have: ";
		problems << argument_count - 1;
		problems << '\n';
	}
}

void lambda_p_repl::echo_binder::operator () ()
{
}