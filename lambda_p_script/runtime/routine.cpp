#include "routine.h"

#include <lambda_p_script/runtime/context.h>
#include <lambda_p_script/nodes/operation.h>

void lambda_p_script::runtime::routine::operator () (std::vector <boost::shared_ptr <lambda_p::node>> & parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	size_t size (operations.size () + 1);
	lambda_p_script::context context (size);
	context.nodes [0].insert (parameters.begin (), parameters.end ());
	for (auto i (operations.begin ()), j (operations.end ()); i != j; ++i)
	{
		(*(*i)) (context);
	}
	results.assign (context.nodes [size - 1].begin (), context.nodes [size - 1].end ());
}