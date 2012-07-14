#include <mu/llvm_/function_type/create.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/values/operation.h>
#include <mu/llvm_/type/node.h>
#include <mu/llvm_/context/node.h>
#include <mu/llvm_/function_type/node.h>
#include <mu/llvm_/set_type/node.h>
#include <mu/llvm_/void_type/node.h>
#include <mu/script/check.h>
#include <mu/script/bool_c/node.h>
#include <mu/llvm_/function_type/divider.h>

#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

#include <sstream>

#include <boost/make_shared.hpp>

#include <gc_cpp.h>

bool mu::llvm_::function_type::create::operator () (mu::script::context & context_a)
{
	bool valid (true);
	if (context_a.parameters_size ())
	{
		auto context (dynamic_cast <mu::llvm_::context::node *> (context_a.parameters (0)));
		if (context != nullptr)
		{
			context_a.reserve (3);
			auto on_args (new (GC) mu::script::bool_c::node (true));
			context_a.locals (0) = on_args;
			auto arguments (new (GC) mu::script::values::operation);
			context_a.locals (1) = arguments;
			auto results (new (GC) mu::script::values::operation);
			context_a.locals (2) = results;
			for (auto i (context_a.parameters_begin () + 1), j (context_a.parameters_end ()); i != j; ++i)
			{
				auto divider (dynamic_cast <mu::llvm_::function_type::divider *> (*i));
				if (divider != nullptr)
				{
					if (!on_args->value)
					{
						valid = false;
						context_a.errors (L"Divider can only be used once in function_type create");
					}
					else
					{
						on_args->value = false;
					}
				}
				else
				{
					if (on_args->value)
					{
						arguments->values.push_back (*i);
					}
					else
					{
						results->values.push_back (*i);
					}
				}
			}
			if (valid)
			{
				std::vector <mu::llvm_::type::node *> arguments_l;
				for (auto i (arguments->values.begin ()), j (arguments->values.end ()); i != j; ++i)
				{
					auto type (dynamic_cast <mu::llvm_::type::node *> (*i));
					if (type != nullptr)
					{
						arguments_l.push_back (type);
					}
					else
					{
						valid = false;
					}
				}
				std::vector <mu::llvm_::type::node *> results_l;
				for (auto i (results->values.begin ()), j (results->values.end ()); i != j; ++i)
				{
					auto type (dynamic_cast <mu::llvm_::type::node *> (*i));
					if (type != nullptr)
					{
						results_l.push_back (type);
					}
					else
					{
						valid = false;
					}
				}
				if (valid)
				{
					if (results_l.size () == 0)
					{				
						context_a.push (new (GC) mu::llvm_::function_type::node (context, arguments_l, new (GC) mu::llvm_::void_type::node (context)));
					}
					else if (results_l.size () == 1)
					{
						context_a.push (new (GC) mu::llvm_::function_type::node (context, arguments_l, results_l [0]));
					}
					else
					{
						context_a.push (new (GC) mu::llvm_::function_type::node (context, arguments_l, new (GC) mu::llvm_::set_type::node (context, results_l)));
					}
				}
			}
		}
		else
		{
			context_a.errors (L"Function_type create requires argument one to be a context");
		}
	}
	else
	{
		context_a.errors (L"Function_type create requires at least one argument");
		valid = false;
	}
	return valid;
}

std::wstring mu::llvm_::function_type::create::name ()
{
	return std::wstring (L"mu::llvm_::function_type::create");
}