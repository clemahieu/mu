#include "routine.h"

#include <core/errors/error_target.h>
#include <lambda_p_script/context.h>
#include <lambda_p_script/operation.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/identity/operation.h>
#include <lambda_p_script/values/operation.h>

#include <boost/make_shared.hpp>

lambda_p_script::routine::routine (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a)
	: cluster (cluster_a)
{
}

void lambda_p_script::routine::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	size_t size (calls.size ());
	std::vector <boost::shared_ptr <mu::core::node>> values_l (parameters.begin (), parameters.end ());
	auto values (boost::make_shared <lambda_p_script::values::operation> (values_l));
	lambda_p_script::context context (cluster, values, size);
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