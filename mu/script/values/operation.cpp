#include "operation.h"

#include <mu/script/check.h>

mu::script::values::operation::operation ()
{
}

mu::script::values::operation::operation (std::vector <boost::shared_ptr <mu::core::node>> values_a)
	: values (values_a)
{
}

void mu::script::values::operation::operator () (mu::script::context & context_a)
{
	if (mu::script::check <> () (context_a))
	{
		context_a.results.insert (context_a.results.end (), values.begin (), values.end ());
	}
}

size_t mu::script::values::operation::count ()
{
	return 0 ;
}