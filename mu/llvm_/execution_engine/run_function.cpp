#include <mu/llvm_/execution_engine/run_function.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/execution_engine/node.h>
#include <mu/llvm_/function/node.h>
#include <mu/llvm_/execution_engine/generic_value/node.h>
#include <mu/script/context.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>

#include <sstream>

bool mu::llvm_::execution_engine::run_function::operator () (mu::script::context & context_a)
{
	bool valid (true);
	if (context_a.parameters_size () > 1)
	{
		auto one (boost::dynamic_pointer_cast <mu::llvm_::execution_engine::node> (context_a.parameters (0)));
		auto two (boost::dynamic_pointer_cast <mu::llvm_::function::node> (context_a.parameters (1)));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				perform_internal (context_a, one, two->function ());
			}
			else
			{
				assert (false);
				//auto two (boost::dynamic_pointer_cast <mu::llvm_::function_pointer::node> (parameters [1]));
				//if (two.get () != nullptr)
				//{
				//	auto function (llvm::dyn_cast <llvm::Function> (two->value ()));
				//	if (function != nullptr)
				//	{
				//		perform_internal (errors_a, one, function, parameters, results);
				//	}
				//	else
				//	{
				//		std::wstringstream message;
				//		message << L"Function argument to operation: ";
				//		message << name ();
				//		message << L" can only be an llvm::Function";
				//		(*errors_a) (message.str ());
				//	}
				//}
				//else
				//{
				//	invalid_type (errors_a, parameters [1], 1);
				//}
			}
		}
		else
		{
			//invalid_type (context_a.errors, context_a.parameters [0], 0);
		}
	}
	else
	{
		std::wstringstream message;
		message << L"Operation: ";
		message << name ();
		message << L" requires at least two arguments";
		context_a.errors (message.str ());
		valid = false;
	}
	return valid;
}

std::wstring mu::llvm_::execution_engine::run_function::name ()
{
	return std::wstring (L"mu::llvm_::execution_engine::run_function");
}

void mu::llvm_::execution_engine::run_function::perform_internal (mu::script::context & context_a, boost::shared_ptr <mu::llvm_::execution_engine::node> one, llvm::Function * function)
{
	bool good (true);
	std::vector <llvm::GenericValue> arguments;
	for (auto i (context_a.parameters_begin () + 2), j (context_a.parameters_end ()); i != j && good; ++i)
	{
		auto value (boost::dynamic_pointer_cast <mu::llvm_::execution_engine::generic_value::node> (*i));
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
			context_a.errors (message.str ());
			good = false;
		}
	}
	auto result (one->engine->runFunction (function, arguments));
	context_a.push (boost::shared_ptr <mu::core::node> (new mu::llvm_::execution_engine::generic_value::node (result)));
}