#include <mu/script/topology/operation.h>

#include <mu/script/check.h>
#include <mu/script/context.h>
#include <mu/core/routine.h>
#include <mu/script/topology/core.h>
#include <mu/script/topology/node.h>

bool mu::script::topology::operation::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::core::routine> () (context_a));
	if (valid)
	{
		auto routine (static_cast <mu::core::routine *> (context_a.parameters (0)));
		mu::script::topology::core core (routine->body);
		if (core.acyclic)
		{
			context_a.push (core.topology);
		}
		else
		{
			context_a.errors (L"Routine contains cycles");
			valid = false;
		}
	}
	return valid;
}