#include "operation.h"

void mu::script::print::operation::perform (mu::script::context & context_a)
{
	for (auto i (context_a.parameters.begin ()), j (context_a.parameters.end ()); i != j; ++i)
	{
		std::wcout << (*i)->debug ();
		std::wcout << L'\n';
	}
}

std::wstring mu::script::print::operation::name ()
{
	return std::wstring (L"mu::script::print::operation");
}