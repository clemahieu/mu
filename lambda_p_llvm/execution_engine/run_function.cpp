#include "run_function.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/execution_engine/node.h>
#include <lambda_p_llvm/function_pointer/node.h>
#include <lambda_p_llvm/execution_engine/generic_value/node.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>

#include <sstream>

void lambda_p_llvm::execution_engine::run_function::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 1)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine::node> (parameters [0]));
		auto two (boost::dynamic_pointer_cast <lambda_p_llvm::function_pointer::node> (parameters [1]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				auto function (llvm::dyn_cast <llvm::Function> (two->value ()));
				if (function != nullptr)
				{
					bool good (true);
					std::vector <llvm::GenericValue> arguments;
					auto i (parameters.begin () + 2);
					auto j (parameters.end ());
					for (; i != j && good; ++i)
					// for (auto i (parameters.begin () + 2), j (parameters.end ()); i != j && good; ++i) Error	11	error C3538: in a declarator-list 'auto' must always deduce to the same type	C:\lambda-p\lambda_p_llvm\execution_engine\run_function.cpp	25	1	lambda_p_llvm
					{
						auto value (boost::dynamic_pointer_cast <lambda_p_llvm::execution_engine::generic_value::node> (*i));
						if (value.get () != nullptr)
						{
							arguments.push_back (value->value);
						}
						else
						{
							std::wstringstream message;
							message << L"Arguments to: ";
							message << name ();
							message << L" must be generic_value, have: ";
							message << (*i)->name ();
							(*errors_a) (message.str ());
							good = false;
						}
					}
					auto result (one->engine->runFunction (function, arguments));
					if (two->multiple_return)
					{
						assert (false);
					}
					else
					{
						results.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_llvm::execution_engine::generic_value::node (result)));
					}
				}
				else
				{
					std::wstringstream message;
					message << L"Value is not a function type";
					(*errors_a) (message.str ());
				}
			}
			else
			{
				invalid_type (errors_a, parameters [1], 1);
			}
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" requires at least two arguments";
	}
}

std::wstring lambda_p_llvm::execution_engine::run_function::name ()
{
	return std::wstring (L"lambda_p_llvm::execution_engine::run_function");
}