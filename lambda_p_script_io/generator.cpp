#include "generator.h"

#include <lambda_p_script_io/routine.h>
#include <lambda_p_script/routine.h>
#include <lambda_p/call.h>
#include <lambda_p_script_io/call.h>
#include <lambda_p_script/call.h>

lambda_p_script_io::generator::generator (lambda_p_script_io::routine & routine_a)
	: result (new lambda_p_script::routine)
{
	size_t open (1);
	for (auto i (routine_a.expressions.begin ()), j (routine_a.expressions.end ()); i != j; ++i, ++open)
	{
		reservation.insert (std::map <boost::shared_ptr <lambda_p::call>, size_t>::value_type (*i, open));
		auto call_l (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (open)));
		++open;
		result->calls.push_back (call_l);
		auto item (*i);
		for (auto k (item->dependencies.begin ()), l (item->dependencies.end ()); k != l; ++k)
		{
			lambda_p_script_io::call call (*this, call_l, *k);
		}
	}
}