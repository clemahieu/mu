#include "routine.h"

#include <lambda_p/routine.h>
#include <lambda_p/order.h>
#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/type/node.h>
#include <lambda_p_llvm/argument/node.h>

#include <llvm/DerivedTypes.h>
#include <llvm/BasicBlock.h>
#include <llvm/Argument.h>

#include <map>
#include <sstream>

lambda_p_llvm_io::routine::routine (boost::shared_ptr <lambda_p::errors::error_target> errors_a, boost::shared_ptr <lambda_p::routine> routine_a, boost::shared_ptr <lambda_p_llvm::module::node> module_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters)
{	
	bool good (true);
	lambda_p::order order (routine_a->body, routine_a->parameters);
	std::map <boost::shared_ptr <lambda_p::expression>, std::vector <boost::shared_ptr <lambda_p_llvm::value::node>>> values;
	auto i (parameters.begin () + 2);
	auto j (parameters.end ());
	for (; i != j; ++i)
	{
		auto type (boost::dynamic_pointer_cast <lambda_p_llvm::type::node> (*i));
		if (type.get () != nullptr)
		{
			values [routine_a->parameters].push_back (boost::shared_ptr <lambda_p_llvm::argument::node> (new lambda_p_llvm::argument::node (new llvm::Argument (type->type ()))));
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
		for (auto i (order.expressions.begin ()), j (order.expressions.end ()); i != j; ++i)
		{

		}
	}
}