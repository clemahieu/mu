#include "builder.h"

#include <lambda_p/binder/list_binder.h>
#include <lambda_p_kernel/parser_factories/data_factory.h>

lambda_p_kernel::builder::builder ()
	: lambda_p::builder (keywords (), injected_declarations (), injected_references ())
{
}

std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>> lambda_p_kernel::builder::keywords ()
{
	std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>> result;
	result.insert (std::map <std::wstring, boost::shared_ptr <lambda_p::parser::state_factory>>::value_type (std::wstring (L"`"), boost::shared_ptr <lambda_p::parser::state_factory> (new lambda_p_kernel::parser_factories::data_factory)));
	return result;
}

std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> lambda_p_kernel::builder::injected_declarations ()
{
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> result;
	result.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"~"), boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::list_binder)));
	return result;
}