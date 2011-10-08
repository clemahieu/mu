#include "argument_binder.h"

#include <lambda_p_llvm/value.h>
#include <lambda_p/errors/binder_string_error.h>
#include <lambda_p/binder/routine_instances.h>

lambda_p_llvm::argument_binder::argument_binder(void)
{
}

void lambda_p_llvm::argument_binder::apply (::std::vector < ::llvm::Value *> & arguments, ::std::vector < size_t>::iterator argument, ::std::vector < size_t>::iterator argument_end, ::llvm::FunctionType::param_iterator parameter, ::llvm::FunctionType::param_iterator parameter_end, ::lambda_p::binder::routine_instances & instances, ::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > & problems)
{
	while (argument != argument_end && parameter != parameter_end)
	{
		::boost::shared_ptr < ::lambda_p::binder::node_instance> value_instance (instances [*argument]);
		::boost::shared_ptr < ::lambda_p_llvm::value> value (::boost::dynamic_pointer_cast < ::lambda_p_llvm::value> (value_instance));
		if (value.get () != NULL)
		{
			if (value->type () == *parameter)
			{
				arguments.push_back (value->operator() ());
			}
			else
			{
				problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::binder_string_error (::std::wstring (L"argument_binder"), ::std::wstring (L"Argument type does not match parameter type"))));
			}
		}
		else
		{
			problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::binder_string_error (::std::wstring (L"argument_binder"), ::std::wstring (L"Argument is not a value"))));
		}
		++argument;
		++parameter;
	}
	if ((argument == argument_end) != (parameter == parameter_end))
	{
		problems.push_back (::boost::shared_ptr < ::lambda_p::errors::error> (new ::lambda_p::errors::binder_string_error (::std::wstring (L"argument_binder"), ::std::wstring (L"Incorrect number of arguments"))));
	}
}