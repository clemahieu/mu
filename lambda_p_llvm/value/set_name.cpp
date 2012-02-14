#include "set_name.h"

#include <lambda_p_llvm/value/node.h>
#include <lambda_p_script/astring/node.h>

#include <llvm/Value.h>
#include <llvm/ADT/Twine.h>

void lambda_p_llvm::value::set_name::operator () (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <lambda_p_script::astring::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			one->value ()->setName (llvm::Twine (two->string));
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

size_t lambda_p_llvm::value::set_name::count ()
{
	return 2;
}