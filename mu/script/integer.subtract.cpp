#include <mu/script/integer.subtract.h>

#include <mu/script/integer.node.h>

void mu::script::integer::subtract::operator () (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	auto one (boost::dynamic_pointer_cast <mu::script::integer::node> (parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::integer::node> (parameters [1]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			results.push_back (boost::shared_ptr <mu::core::node> (new mu::script::integer::node (one->value - two->value)));
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

size_t mu::script::integer::subtract::count ()
{
	return 2;
}

std::wstring mu::script::integer::subtract::name ()
{
	return std::wstring (L"mu::script::integer::subtract");
}
