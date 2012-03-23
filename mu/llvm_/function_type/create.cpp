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

bool mu::llvm_::function_type::create::operator () (mu::script::context & context_a)
{
	bool valid (true);
	if (context_a.parameters_size ())
	{
		auto context (boost::dynamic_pointer_cast <mu::llvm_::context::node> (context_a.parameters (0)));
		if (context.get () != nullptr)
		{
			context_a.reserve (3);
			auto on_args (boost::make_shared <mu::script::bool_c::node> (true));
			context_a.locals (0) = on_args;
			auto arguments (boost::make_shared <mu::script::values::operation> ());
			context_a.locals (1) = arguments;
			auto results (boost::make_shared <mu::script::values::operation> ());
			context_a.locals (2) = results;
			for (auto i (context_a.parameters_begin () + 1), j (context_a.parameters_end ()); i != j && on_args->value; ++i)
			{
				auto divider (boost::dynamic_pointer_cast <mu::llvm_::function_type::divider> (*i));
				if (divider.get () != nullptr)
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
				std::vector <boost::shared_ptr <mu::llvm_::type::node>> arguments_l;
				for (auto i (arguments->values.begin ()), j (arguments->values.end ()); i != j; ++i)
				{
					auto type (boost::dynamic_pointer_cast <mu::llvm_::type::node> (*i));
					if (type.get () != nullptr)
					{
						arguments_l.push_back (type);
					}
					else
					{
						valid = false;
					}
				}
				std::vector <boost::shared_ptr <mu::llvm_::type::node>> results_l;
				for (auto i (results->values.begin ()), j (results->values.end ()); i != j; ++i)
				{
					auto type (boost::dynamic_pointer_cast <mu::llvm_::type::node> (*i));
					if (type.get () != nullptr)
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
						context_a.push (boost::make_shared <mu::llvm_::function_type::node> (context, arguments_l, boost::make_shared <mu::llvm_::void_type::node> (context)));
					}
					else if (results_l.size () == 1)
					{
						context_a.push (boost::make_shared <mu::llvm_::function_type::node> (context, arguments_l, results_l [0]));
					}
					else
					{
						context_a.push (boost::make_shared <mu::llvm_::function_type::node> (context, arguments_l, boost::make_shared <mu::llvm_::set_type::node> (context, results_l)));
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