#include "create.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/context/node.h>
#include <lambda_p_llvm/apint/node.h>
#include <lambda_p_llvm/struct_type/node.h>

#include <llvm/DerivedTypes.h>

#include <sstream>

#include <boost/make_shared.hpp>

void lambda_p_llvm::struct_type::create::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	if (parameters.size () > 0)
	{
		auto one (boost::dynamic_pointer_cast <lambda_p_llvm::context::node> (parameters [0]));
		if (one.get () != nullptr)
		{
			size_t position (1);
			std::vector <boost::shared_ptr <lambda_p_llvm::type::node>> types;
			for (auto i (parameters.begin ()), j (parameters.end ()); i != j && !(*errors_a) (); ++i, ++position)
			{
				auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (*i));
				if (type.get () != nullptr)
				{
					types.push_back (type);
				}
				else
				{
					invalid_type (errors_a, *i, position);
				}
			}
			if (!(*errors_a) ())
			{
				results.push_back (boost::make_shared <lambda_p_llvm::struct_type::node> (one, types));
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
		message << name ();
		message << L" requires at least one argument";
		(*errors_a) (message.str ());
	}
}