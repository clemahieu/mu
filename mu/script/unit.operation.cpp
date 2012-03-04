#include <mu/script/unit.operation.h>

void mu::script::unit::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
}

std::wstring mu::script::unit::operation::name ()
{
	return std::wstring (L"mu::script::unit::operation");
}
