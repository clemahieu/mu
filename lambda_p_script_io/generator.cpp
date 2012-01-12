#include "generator.h"

#include <lambda_p_script/routine.h>
#include <lambda_p/call.h>
#include <lambda_p_script_io/call.h>
#include <lambda_p_script/call.h>
#include <lambda_p/parameters.h>

lambda_p_script_io::generator::generator (std::vector <boost::shared_ptr <lambda_p::call>> & expressions_a, boost::shared_ptr <lambda_p::parameters> parameters_a)
	: result (new lambda_p_script::routine)
{
	reservations.insert (std::map <boost::shared_ptr <lambda_p::expression>, size_t>::value_type (parameters_a, 0));
	size_t open (1);
	for (auto i (expressions_a.begin ()), j (expressions_a.end ()); i != j; ++i, ++open)
	{
		reservations.insert (std::map <boost::shared_ptr <lambda_p::expression>, size_t>::value_type (*i, open));
		auto call_l (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (open)));
		result->calls.push_back (call_l);
		auto item (*i);
		for (auto k (item->dependencies.begin ()), l (item->dependencies.end ()); k != l; ++k)
		{
			lambda_p_script_io::call call (reservations, call_l, *k);
		}
	}
}