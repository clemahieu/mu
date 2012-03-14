#include "routine.h"

#include <mu/script/runtime/routine.h>
#include <mu/core/expression.h>
#include <mu/script_io/expression.h>
#include <mu/script/runtime/call.h>
#include <mu/script/identity/operation.h>
#include <mu/core/order.h>
#include <mu/core/routine.h>

mu::script_io::routine::routine (mu::script_io::cluster & cluster_a, boost::shared_ptr <mu::core::routine> routine_a, boost::shared_ptr <mu::script::runtime::routine> result_a)
{
	mu::core::order order (routine_a->body);
	size_t open (0);
	for (auto i (order.expressions.begin ()), j (order.expressions.end ()); i != j; ++i, ++open)
	{
		reservations.insert (std::map <boost::shared_ptr <mu::core::expression>, size_t>::value_type (*i, open));
		auto call_l (boost::shared_ptr <mu::script::runtime::call> (new mu::script::runtime::call (open)));
		result_a->calls.push_back (call_l);
		auto item (*i);
		for (auto k (item->dependencies.begin ()), l (item->dependencies.end ()); k != l; ++k)
		{
			mu::script_io::expression expression (cluster_a, reservations, call_l, *k);
		}
	}
}