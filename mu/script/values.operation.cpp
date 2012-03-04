#include <mu/script/values.operation.h>

mu::script::values::operation::operation ()
{
}

mu::script::values::operation::operation (std::vector <boost::shared_ptr <mu::core::node>> values_a)
	: values (values_a)
{
}

void mu::script::values::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	results.insert (results.end (), values.begin (), values.end ());
}

size_t mu::script::values::operation::count ()
{
	return 0 ;
}
