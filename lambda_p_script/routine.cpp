#include "routine.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/context.h>
#include <lambda_p_script/operation.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/identity/operation.h>

void lambda_p_script::routine::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p_script::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	size_t size (calls.size () + 1);
	lambda_p_script::context context (size);
	context.nodes [0].push_back (boost::shared_ptr <lambda_p::node> (new lambda_p_script::identity::operation));
	context.nodes [0].insert (context.nodes [0].end (), parameters.begin (), parameters.end ());
	for (auto i (calls.begin ()), j (calls.end ()); i != j && !(*errors_a) (); ++i)
	{
		(*(*i)) (errors_a, context);
	}
	results.assign (context.nodes [size - 1].begin (), context.nodes [size - 1].end ());
}

std::wstring lambda_p_script::routine::name ()
{
	return std::wstring (L"lambda_p_script::routine");
}