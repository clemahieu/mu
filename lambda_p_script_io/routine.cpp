#include "routine.h"

#include <lambda_p_script/routine.h>
#include <core/expression.h>
#include <lambda_p_script_io/expression.h>
#include <lambda_p_script/call.h>
#include <lambda_p_script/identity/operation.h>
#include <core/order.h>
#include <core/routine.h>

lambda_p_script_io::routine::routine (boost::shared_ptr <lambda_p_script::cluster::node> cluster_a, boost::shared_ptr <mu::core::routine> routine_a, boost::shared_ptr <lambda_p_script::routine> result_a)
{
	mu::core::order order (routine_a->body);
	size_t open (0);
	for (auto i (order.expressions.begin ()), j (order.expressions.end ()); i != j; ++i, ++open)
	{
		reservations.insert (std::map <boost::shared_ptr <mu::core::expression>, size_t>::value_type (*i, open));
		auto call_l (boost::shared_ptr <lambda_p_script::call> (new lambda_p_script::call (open, (*i)->context)));
		result_a->calls.push_back (call_l);
		auto item (*i);
		for (auto k (item->dependencies.begin ()), l (item->dependencies.end ()); k != l; ++k)
		{
			lambda_p_script_io::expression expression (cluster_a, reservations, call_l, *k);
		}
	}
}