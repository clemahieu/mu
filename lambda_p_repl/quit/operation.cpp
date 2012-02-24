#include "operation.h"

#include <lambda_p_repl/repl.h>

lambda_p_repl::quit::operation::operation (lambda_p_repl::repl & repl_a)
	: repl (repl_a)
{
}

void lambda_p_repl::quit::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	repl.stop ();
}

size_t lambda_p_repl::quit::operation::count ()
{
	return 0;
}

std::wstring lambda_p_repl::quit::operation::name ()
{
	return std::wstring (L"lambda_p_repl::quit::operation");
}