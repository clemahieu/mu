#include <mu/test_entry/script/chain/ten_count.h>

#include <mu/script/integer_node.h>
#include <mu/script/bool_c_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

mu::script_test::chain::ten_count::ten_count ()
	: count_m (10)
{
}

bool mu::script_test::chain::ten_count::operator () (mu::script::context & context_a)
{
	bool valid (mu::core::check <mu::script::integer::node> (context_a));
	if (valid)
	{
		auto one (static_cast <mu::script::integer::node *> (context_a.parameters (0)));
		--count_m;
		context_a.push (new (GC) mu::script::integer::node (one->value - 1));
		context_a.push (new (GC) mu::script::bool_c::node (count_m == 0));
	}
	return valid;
}