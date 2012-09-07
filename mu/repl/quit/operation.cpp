#include <mu/repl/quit/operation.h>

#include <mu/core/check.h>
#include <mu/repl/repl.h>
#include <mu/script/context.h>

mu::repl::quit::operation::operation (mu::repl::repl & repl_a)
	: repl (repl_a)
{
}

bool mu::repl::quit::operation::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <> (context_a));
	if (result)
	{
		repl.stop ();
	}
	return result;
}