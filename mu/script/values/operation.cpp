#include <mu/script/values/operation.h>

#include <mu/script/check.h>

mu::script::values::operation::operation ()
{
}

mu::script::values::operation::operation (std::vector <boost::shared_ptr <mu::core::node>> values_a)
	: values (values_a)
{
}

bool mu::script::values::operation::operator () (mu::script_runtime::context & context_a)
{
	bool result (mu::script::check <> () (context_a));
	if (result)
	{
		for (auto i (values.begin ()), j (values.end ()); i != j; ++i)
		{
			context_a.push (*i);
		}
	}
	return result;
}