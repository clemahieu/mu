#include "operation.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_llvm/value/node.h>

#include <sstream>

void lambda_p_llvm::identity::operation::operator() (boost::shared_ptr <lambda_p::errors::error_target> errors_a, llvm::BasicBlock * & context_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters_a, std::vector <boost::shared_ptr <lambda_p::node>> & results_a)
{
	for (auto i (parameters_a.begin ()), j (parameters_a.end ()); i != j; ++i)
	{
		auto value (boost::dynamic_pointer_cast <lambda_p_llvm::value::node> (*i));
		if (value.get () != nullptr)
		{
			results_a.push_back (value);
		}
		else
		{
			std::wstringstream message;
			message << L"Identity operation passed non-value argument: ";
			message << (*i)->name ();
			(*errors_a) (message.str ());
		}
	}
}