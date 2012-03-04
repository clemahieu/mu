#include <mu/script_test/chain.ten_count.h>

#include <mu/script/integer.node.h>
#include <mu/script/bool_c.node.h>

mu::script_test::chain::ten_count::ten_count ()
	: count_m (10)
{
}

void mu::script_test::chain::ten_count::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::integer::node> (parameters [0]));
	if (one.get () != nullptr)
	{
		--count_m;
		results.push_back (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (one->value - 1)));
		results.push_back (boost::shared_ptr <mu::core::node> (new mu::script::bool_c::node (count_m == 0)));
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

size_t mu::script_test::chain::ten_count::count ()
{
	return 1;
}
