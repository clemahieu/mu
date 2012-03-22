#include <mu/script/runtime/routine.h>

#include <mu/script/context.h>
#include <mu/script/runtime/locals.h>
#include <mu/script/topology/node.h>
#include <mu/script/runtime/expression.h>

#include <boost/make_shared.hpp>

mu::script::runtime::routine::routine (boost::shared_ptr <mu::script::runtime::expression> parameters_a)
	: parameters (parameters_a)
{
}

bool mu::script::runtime::routine::operator () (mu::script::context & context_a)
{
	bool valid (true);
	context_a.reserve (1);
	auto locals (boost::make_shared <mu::script::runtime::locals> ());
	context_a.locals (0) = locals;
	locals->expressions [parameters] = boost::tuple <size_t, size_t> (locals->frame.size (), locals->frame.size () + context_a.parameters_size ());
	for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
	{
		locals->frame.push_back (*i);
	}
	for (auto i (expressions.begin ()), j (expressions.end ()); i != j; ++i)
	{
		context_a.push (*i);
		context_a.push (locals);
		auto valid_l (context_a ());
		valid = valid && valid_l;
		if (valid_l)
		{
			locals->expressions [*i] = boost::tuple <size_t, size_t> (locals->frame.size (), locals->frame.size () + context_a.working_size ());
			for (auto k (context_a.working_begin ()), l (context_a.working_end ()); k != l; ++k)
			{
				locals->frame.push_back (*k);
			}
		}
		else
		{
			locals->expressions [*i] = boost::tuple <size_t, size_t> (~0, ~0);
		}
		context_a.drop ();
	}
	return valid;
}