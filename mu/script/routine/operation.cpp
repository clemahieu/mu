#include <mu/script/routine/operation.h>

#include <mu/script/context.h>
#include <mu/script/values/operation.h>
#include <mu/core/routine.h>
#include <mu/script/check.h>
#include <mu/script/context.h>
#include <mu/script/routine/locals.h>
#include <mu/core/expression.h>
#include <mu/script/routine/node.h>

#include <boost/make_shared.hpp>

bool mu::script::routine::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.working_size () > 0)
	{
		auto routine (boost::dynamic_pointer_cast <mu::core::routine> (context_a.working (0)));
		if (routine.get () != nullptr)
		{
			auto locals (boost::make_shared <mu::script::routine::locals> ());
			auto parameters (boost::make_shared <mu::script::values::operation> ());
			for (auto i (context_a.working_begin ()), j (context_a.working_end ()); i != j; ++i)
			{
				parameters->values.push_back (*i);
			}
			context_a.reserve (1);
			context_a.locals (0) = locals;
			context_a.push (boost::make_shared <mu::script::routine::node> ());
			context_a.push (locals);
			context_a.push (parameters);
			context_a.push (routine->body);
			result = context_a ();
		}
		else
		{
			mu::script::invalid_type (context_a, typeid (*context_a.working (0)), typeid (mu::core::routine), 0);
			result = false;
		}
	}
	else
	{
		context_a.errors (L"Routine operation must have at least one parameter");
		result = false;
	}
	return result;
}