#include "create.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/values/operation.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/function_type/node.h>
#include <lambda_p_llvm/set_type/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::function_type::create::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	auto context (boost::dynamic_pointer_cast <lambda_p_llvm::context::node> (parameters [0]));
	auto one (boost::dynamic_pointer_cast <lambda_p_script::values::operation> (parameters [1]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::values::operation> (parameters [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> arguments;
			std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> results;
			for (auto i (one->values.begin ()), j (one->values.end ()); i != j; ++i)
			{
				auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (*i));
				if (type.get () != nullptr)
				{
					arguments.push_back (type);
				}
				else
				{
					std::wstringstream message;
					message << L"Expecting type, have: ";
					message << (*i)->name ();
					(*errors_a) (message.str ());
				}
			}
			for (auto i (two->values.begin ()), j (two->values.end ()); i != j; ++i)
			{
				auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (*i));
				if (type.get () != nullptr)
				{
					results.push_back (type);
				}
				else
				{
					std::wstringstream message;
					message << L"Expecting type, have: ";
					message << (*i)->name ();
					(*errors_a) (message.str ());
				}
			}
			results_a.push_back (boost::make_shared <lambda_p_llvm::function_type::node> (context, arguments, boost::make_shared <lambda_p_llvm::set_type::node> (context, results)));
		}
		else
		{
			invalid_type (errors_a, parameters [0], 0);
		}
	}
	else
	{
			invalid_type (errors_a, parameters [1], 1);
	}
}

size_t lambda_p_llvm::function_type::create::count ()
{
	return 3;
}