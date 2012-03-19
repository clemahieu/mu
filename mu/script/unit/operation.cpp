#include <mu/script/unit/operation.h>

bool mu::script::unit::operation::operator () (mu::script_runtime::context & context_a)
{
	return true;
}

std::wstring mu::script::unit::operation::name ()
{
	return std::wstring (L"mu::script::unit::operation");
}