#include <mu/script/values/create.h>

#include <mu/script/values/operation.h>
#include <mu/script_runtime/context.h>

#include <boost/make_shared.hpp>

bool mu::script::values::create::operator () (mu::script_runtime::context & context_a)
{
	bool result (true);
	std::vector <boost::shared_ptr <mu::core::node>> values;
	for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
	{
		values.push_back (*i);
	}
	context_a.push (boost::make_shared <mu::script::values::operation> (values));
	return result;
}