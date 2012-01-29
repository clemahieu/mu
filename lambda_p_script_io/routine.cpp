#include "routine.h"

#include <lambda_p_script/routine.h>
#include <lambda_p/expression.h>
#include <lambda_p_script_io/expression.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/identity/operation.h>

lambda_p_script_io::routine::routine (std::vector <boost::shared_ptr <lambda_p::expression>> & expressions_a, boost::shared_ptr <lambda_p::expression> parameters_a)
	: result (new lambda_p_script::routine)
{
	reservations.insert (std::map <boost::shared_ptr <lambda_p::expression>, size_t>::value_type (parameters_a, 0));
	size_t open (1);
	for (auto i (expressions_a.begin ()), j (expressions_a.end ()); i != j; ++i, ++open)
	{
		reservations.insert (std::map <boost::shared_ptr <lambda_p::expression>, size_t>::value_type (*i, open));
		auto call_l (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (open, (*i)->context)));
		result->calls.push_back (call_l);
		auto item (*i);
		for (auto k (item->dependencies.begin ()), l (item->dependencies.end ()); k != l; ++k)
		{
			lambda_p_script_io::expression expression (reservations, call_l, *k);
		}
	}
}