#include <mu/script/integer.equal.h>

#include <mu/core/errors.error_target.h>
#include <mu/script/integer.node.h>
#include <mu/script/bool_c.node.h>

void mu::script::integer::equal::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::integer::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::integer::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			results.push_back (boost::shared_ptr <mu::script::bool_c::node> (new mu::script::bool_c::node (one->value == two->value)));
		}
		else
		{
			invalid_type (errors_a, parameters [1], 1);
		}
	}
	else
	{
		invalid_type (errors_a, parameters [0], 0);
	}
}

std::wstring mu::script::integer::equal::name ()
{
	return std::wstring (L"mu::script::integer::equal");
}

size_t mu::script::integer::equal::count ()
{
	return 2;
}
