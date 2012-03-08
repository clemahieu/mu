#include "operation.h"

void mu::script::identity::operation::perform (mu::script::context & context_a)
{
	context_a.results.insert (context_a.results.end (), context_a.parameters.begin (), context_a.parameters.end ());
}

std::wstring mu::script::identity::operation::name ()
{
	return std::wstring (L"mu::script::identity::operation");
}