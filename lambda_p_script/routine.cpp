#include "routine.h"

#include <lambda_p/errors/error_target.h>
#include <lambda_p_script/context.h>
#include <lambda_p_script/operation.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/identity/operation.h>
#include <lambda_p_script/values/operation.h>

#include <boost/make_shared.hpp>

void lambda_p_script::routine::perform (boost::shared_ptr <lambda_p::errors::error_target> errors_a, lambda_p::segment <boost::shared_ptr <lambda_p::node>> parameters, std::vector <boost::shared_ptr <lambda_p::node>> & results)
{
	size_t size (calls.size ());
	auto values (boost::make_shared <lambda_p_script::values::operation> ());
	values->values.assign (parameters.begin (), parameters.end ());
	lambda_p_script::context context (values, size);
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