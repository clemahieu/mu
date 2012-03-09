#include "operation.h"

#include <mu/script/check.h>

#include <mu/repl/repl.h>

mu::repl::quit::operation::operation (mu::repl::repl & repl_a)
	: repl (repl_a)
{
}

void mu::repl::quit::operation::operator () (mu::script::context & context_a)
{
	if (mu::script::check <> () (context_a))
	{
		repl.stop ();
	}
}

std::wstring mu::repl::quit::operation::name ()
{
	return std::wstring (L"mu::repl::quit::operation");
}