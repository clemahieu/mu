#include <mu/script/values/create.h>

#include <mu/script/values/operation.h>
#include <mu/script/context.h>

#include <boost/make_shared.hpp>

void mu::script::values::create::operator () (mu::script::context & context_a)
{
	std::vector <boost::shared_ptr <mu::core::node>> values;
	for (auto i (context_a.parameters.begin ()), j (context_a.parameters.end ()); i != j; ++i)
	{
		values.push_back (*i);
	}
	context_a.results.push_back (boost::make_shared <mu::script::values::operation> (values));
}