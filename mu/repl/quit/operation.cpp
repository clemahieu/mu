#include <mu/repl/quit/operation.h>

#include <mu/script/check.h>

#include <mu/repl/repl.h>

mu::repl::quit::operation::operation (mu::repl::repl & repl_a)
	: repl (repl_a)
{
}

bool mu::repl::quit::operation::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <> () (context_a));
	if (result)
	{
		repl.stop ();
	}
	return result;
}

mu::string mu::repl::quit::operation::name ()
{
	return mu::string (U"mu::repl::quit::operation");
}