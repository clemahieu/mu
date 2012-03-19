#include <mu/script/print/operation.h>

#include <mu/script_runtime/context.h>

bool mu::script::print::operation::operator () (mu::script_runtime::context & context_a)
{
	bool result (true);
	for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
	{
		std::wcout << (*i)->debug ();
		std::wcout << L'\n';
	}
	return result;
}

std::wstring mu::script::print::operation::name ()
{
	return std::wstring (L"mu::script::print::operation");
}