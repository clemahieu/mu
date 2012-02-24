#include "operation.h"

void lambda_p_script::print::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	for (auto i (parameters.begin ()), j (parameters.end ()); i != j; ++i)
	{
		std::wcout << (*i)->debug ();
		std::wcout << L'\n';
	}
}

std::wstring lambda_p_script::print::operation::name ()
{
	return std::wstring (L"lambda_p_script::print::operation");
}