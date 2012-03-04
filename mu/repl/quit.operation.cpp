#include "operation.h"

#include <mu/repl/repl.h>

mu::repl::quit::operation::operation (mu::repl::repl & repl_a)
	: repl (repl_a)
{
}

void mu::repl::quit::operation::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	repl.stop ();
}

size_t mu::repl::quit::operation::count ()
{
	return 0;
}

std::wstring mu::repl::quit::operation::name ()
{
	return std::wstring (L"mu::repl::quit::operation");
}