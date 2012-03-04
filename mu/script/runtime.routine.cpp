#include <mu/script/runtime.routine.h>

#include <mu/core/errors.error_target.h>
#include <mu/script/runtime.context.h>
#include <mu/script/operation.h>
#include <mu/script/runtime.call.h>
#include <mu/script/identity.operation.h>
#include <mu/script/values.operation.h>

#include <boost/make_shared.hpp>

mu::script::runtime::routine::routine (boost::shared_ptr <mu::script::cluster::node> cluster_a)
	: cluster (cluster_a)
{
}

void mu::script::runtime::routine::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	size_t size (calls.size ());
	std::vector <boost::shared_ptr <mu::core::node>> values_l (parameters.begin (), parameters.end ());
	auto values (boost::make_shared <mu::script::values::operation> (values_l));
	mu::script::runtime::context context (cluster, values, size);
	for (auto i (calls.begin ()), j (calls.end ()); i != j && !(*errors_a) (); ++i)
	{
		(*(*i)) (errors_a, context);
	}
	results.assign (context.nodes [size - 1].begin (), context.nodes [size - 1].end ());
}

std::wstring mu::script::runtime::routine::name ()
{
	return std::wstring (L"mu::script::runtime::routine");
}
