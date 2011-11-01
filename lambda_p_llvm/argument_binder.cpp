#include "argument_binder.h"

#include <lambda_p_llvm/value.h>
#include <lambda_p/errors/binder_string_error.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/errors/error_list.h>

lambda_p_llvm::argument_binder::argument_binder(void)
{
}

void lambda_p_llvm::argument_binder::apply (std::vector <llvm::Value *> & argument_values, boost::shared_ptr <lambda_p::binder::list> arguments, llvm::FunctionType::param_iterator parameter, llvm::FunctionType::param_iterator parameter_end, lambda_p::binder::node_list & nodes, lambda_p::errors::error_list & problems)
{
	auto argument (arguments->nodes.begin ());
	while (argument != arguments->nodes.end () && parameter != parameter_end)
	{
		boost::shared_ptr <lambda_p::binder::node> value_instance (*argument);
		boost::shared_ptr <lambda_p_llvm::value> value (boost::dynamic_pointer_cast <lambda_p_llvm::value> (value_instance));
		if (value.get () != nullptr)
		{
			if (value->type () == *parameter)
			{
				argument_values.push_back (value->operator() ());
			}
			else
			{
				problems (new lambda_p::errors::binder_string_error (std::wstring (L"argument_binder"), std::wstring (L"Argument type does not match parameter type")));
			}
		}
		else
		{
			problems (new lambda_p::errors::binder_string_error (std::wstring (L"argument_binder"), std::wstring (L"Argument is not a value")));
		}
		++argument;
		++parameter;
	}
	if ((argument == arguments->nodes.end ()) != (parameter == parameter_end))
	{
		problems (new lambda_p::errors::binder_string_error (std::wstring (L"argument_binder"), std::wstring (L"Incorrect number of arguments")));
	}
}