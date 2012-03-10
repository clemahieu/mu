#include <mu/script/runtime/routine.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/runtime/frame.h>
#include <mu/script/operation.h>
#include <mu/script/runtime/call.h>
#include <mu/script/identity/operation.h>
#include <mu/script/values/operation.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

mu::script::runtime::routine::routine ()
{
}

void mu::script::runtime::routine::operator () (mu::script::context & context_a)
{
	size_t size (calls.size ());
	std::vector <boost::shared_ptr <mu::core::node>> values_l (context_a.parameters.begin (), context_a.parameters.end ());
	auto values (boost::make_shared <mu::script::values::operation> (values_l));
	mu::script::runtime::frame frame (values, size);
	for (auto i (calls.begin ()), j (calls.end ()); i != j && !(*context_a.errors) (); ++i)
	{
		(*(*i)) (context_a, context_a.errors, frame);
	}
	context_a.results.assign (frame.nodes [size - 1].begin (), frame.nodes [size - 1].end ());
}

std::wstring mu::script::runtime::routine::name ()
{
	return std::wstring (L"mu::script::runtime::routine");
}