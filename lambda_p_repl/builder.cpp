#include "builder.h"

#include <lambda_p_repl/api.h>
#include <lambda_p_llvm/context.h>
#include <lambda_p_llvm/generation_context.h>
#include <lambda_p/binder/list_binder.h>

#include <llvm/Module.h>

lambda_p_repl::builder::builder (boost::shared_ptr <lambda_p::binder::node> environment_a, boost::shared_ptr <lambda_p::binder::node> exec_a)
	: lambda_p::builder (keywords (), injected_declarations (environment_a, exec_a), injected_references ())
{
}

std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> lambda_p_repl::builder::injected_declarations (boost::shared_ptr <lambda_p::binder::node> environment_a, boost::shared_ptr <lambda_p::binder::node> exec_a)
{
	std::vector <std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>>> result;
	result.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"environment"), environment_a));
	result.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"exec"), exec_a));
	result.push_back (std::pair <std::wstring, boost::shared_ptr <lambda_p::binder::node>> (std::wstring (L"~"), boost::shared_ptr <lambda_p::binder::node> (new lambda_p::binder::list_binder)));
	return result;
}