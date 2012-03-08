#include "operation.h"

#include <mu/repl/repl.h>

mu::repl::quit::operation::operation (mu::repl::repl & repl_a)
	: repl (repl_a)
{
}

void mu::repl::quit::operation::operator () (mu::script::context & context_a)
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