#include "call.h"

#include <lambda_p_script/operation.h>

lambda_p_script::call::call (std::vector <size_t> arguments_a, boost::shared_ptr <lambda_p_script::operation> operation_a)
	: arguments (arguments_a),
	operation (operation_a)
{
}

void lambda_p_script::call::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & context, size_t base, size_t open)
{
	context.resize (open + arguments.size ());
	size_t position (0);
	for (auto i (arguments.begin ()), j (arguments.end ()); i != j; ++i, ++position)
	{
		context [open + position] = context [base + *i];
	}
	(*operation) (context, open);
}