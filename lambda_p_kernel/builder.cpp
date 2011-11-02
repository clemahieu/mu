#include "builder.h"

#include <lambda_p/binder/list_binder.h>

lambda_p_kernel::builder::builder ()
	: lambda_p::builder (injected_declarations (), injected_references ())
{
}

std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> lambda_p_kernel::builder::injected_declarations ()
{
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> result;
	result.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"~"), boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::list_binder)));
	return result;
}