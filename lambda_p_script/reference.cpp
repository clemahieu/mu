#include "reference.h"

#include <mu/core/errors/error_target.h>
#include <lambda_p_script/context.h>

#include <sstream>

lambda_p_script::reference::reference (size_t expression_a, size_t index_a)
	: expression (expression_a),
	index (index_a)
{
}

void lambda_p_script::reference::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, lambda_p_script::context & context, std::vector <boost::shared_ptr <mu::core::node>> & target)
{
	assert (context.nodes.size () > expression);
	std::vector <boost::shared_ptr <mu::core::node>> & source (context.nodes [expression]);
	if (source.size () > index)
	{
		target.push_back (source [index]);
	}
	else
	{
		std::wstringstream message;
		message << L"Expression at index: ";
		message << expression;
		message << L" does not have: ";
		message << index;
		message << L" results";
		(*errors_a) (message.str ());
	}
}