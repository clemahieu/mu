#include <mu/script/print/operation.h>

#include <mu/script/context.h>

bool mu::script::print::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
	{
        auto str ((*i)->debug ());
		std::wcout << std::wstring (str.begin (), str.end ());;
		std::wcout << L'\n';
	}
	return result;
}

mu::string mu::script::print::operation::name ()
{
	return mu::string (U"mu::script::print::operation");
}