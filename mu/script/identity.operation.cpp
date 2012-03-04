#include <mu/script/identity.operation.h>

void mu::script::identity::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	results.insert (results.end (), parameters.begin (), parameters.end ());
}

std::wstring mu::script::identity::operation::name ()
{
	return std::wstring (L"mu::script::identity::operation");
}
