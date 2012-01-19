#include "synthesizer.h"

#include <lambda_p/order.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/function/node.h>
#include <lambda_p/routine.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/argument/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Argument.h>

#include <sstream>
#include <map>

void lambda_p_llvm_io::synthesizer::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 1)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p::routine> (parameters [0]));
		auto two (boost::dynamic_pointer_cast <lambda_p_llvm::function::node> (parameters [1]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				bool good (true);
				lambda_p::order order (one->body, one->parameters);
				std::map <boost::shared_ptr <lambda_p::expression>, std::vector <boost::shared_ptr <lambda_p_llvm::value::node>>> values;
				auto i (parameters.begin () + 2);
				auto j (parameters.end ());
				for (; i != j; ++i)
				{
					auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (*i));
					if (type.get () != nullptr)
					{
						values [one->parameters].push_back (boost::shared_ptr <lambda_p_llvm::argument::node> (new lambda_p_llvm::argument::node (new llvm::Argument (type->type ()))));
					}
					else
					{
						good = false;
						std::wstringstream message;
						message << L"Arguments to function must be types, have: ";
						message << (*i)->name ();
						(*errors_a) (message.str ());
					}
				}
				if (good)
				{
					
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
		(*errors_a) (message.str ());
	}
}

std::wstring lambda_p_llvm_io::synthesizer::name ()
{
	return std::wstring (L"lambda_p_llvm_io::synthesizer");
}