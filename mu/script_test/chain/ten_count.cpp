#include <mu/script_test/chain/ten_count.h>

#include <mu/script/integer/node.h>
#include <mu/script/bool_c/node.h>
#include <mu/script/check.h>

mu::script_test::chain::ten_count::ten_count ()
	: count_m (10)
{
}

bool mu::script_test::chain::ten_count::operator () (mu::script::context & context_a)
{
	bool valid (mu::script::check <mu::script::integer::node> () (context_a));
	if (valid)
	{
		auto one (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters (0)));
		--count_m;
		context_a.push (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (one->value - 1)));
		context_a.push (boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (count_m == 0)));
	}
	return valid;
}