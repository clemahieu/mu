#include "fixed.h"

void mu::script::fixed::perform (mu::script::context & context_a)
{
	if (check_count (context_a.errors, context_a.parameters, count ()))
	{
		(*this) (context_a);
	}
}