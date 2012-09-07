#include <mu/llvm_/execution_engine_run_function.h>

#include <mu/core/errors/error_target.h>
#include <mu/llvm_/execution_engine_node.h>
#include <mu/llvm_/function_node.h>
#include <mu/llvm_/execution_engine_generic_value_node.h>
#include <mu/script/context.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>

#include <sstream>

#include <gc_cpp.h>

bool mu::llvm_::execution_engine::run_function::operator () (mu::script::context & context_a)
{
	bool valid (true);
	if (context_a.parameters_size () > 1)
	{
		auto one (dynamic_cast <mu::llvm_::execution_engine::node *> (context_a.parameters (0)));
		auto two (dynamic_cast <mu::llvm_::function::node *> (context_a.parameters (1)));
		if (one != nullptr)
		{
			if (two != nullptr)
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
				//		message << U"Function argument to operation: ";
				//		message << name ();
				//		message << U" can only be an llvm::Function";
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
		mu::stringstream message;
		message << U"Operation: ";
		message << name ();
		message << U" requires at least two arguments";
		context_a.errors (message.str ());
		valid = false;
	}
	return valid;
}

void mu::llvm_::execution_engine::run_function::perform_internal (mu::script::context & context_a, mu::llvm_::execution_engine::node * one, llvm::Function * function)
{
	bool good (true);
	std::vector <llvm::GenericValue> arguments;
	for (auto i (context_a.parameters_begin () + 2), j (context_a.parameters_end ()); i != j && good; ++i)
	{
		auto value (dynamic_cast <mu::llvm_::execution_engine::generic_value::node *> (*i));
		if (value != nullptr)
		{
			arguments.push_back (value->value);
		}
		else
		{
			mu::stringstream message;
			message << U"Arguments to: ";
			message << name ();
			message << U" must be generic_value, have: ";
			message << (*i)->name ();
			context_a.errors (message.str ());
			good = false;
		}
	}
	auto result (one->engine->runFunction (function, arguments));
	context_a.push (new (GC) mu::llvm_::execution_engine::generic_value::node (result));
}