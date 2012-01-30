#include "synthesizer.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm_io/routine.h>
#include <lambda_p_llvm/module/node.h>
#include <lambda_p/cluster.h>
#include <lambda_p_llvm/function_pointer/node.h>
#include <lambda_p_llvm/cluster.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm_io::synthesizer::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 1)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p::cluster> (parameters [0]));
		auto two (boost::dynamic_pointer_cast <lambda_p_llvm::module::node> (parameters [1]));
		if (one.get () != nullptr)
		{
			if (two.get () != nullptr)
			{
				auto result (boost::make_shared <lambda_p_llvm::cluster> ());
				for (auto i (one->routines.begin ()), j (one->routines.end ()); i != j; ++i)
				{
					lambda_p_llvm_io::routine routine (errors_a, *i, two, lambda_p::segment <boost::shared_ptr <lambda_p::node>> (parameters.lower + 2, parameters.source));
					result->routines.push_back (routine.result);
				}
				if (!(*errors_a) ())
				{
					results.push_back (result);
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