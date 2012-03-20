#include <mu/script/if_c/operation.h>

#include <mu/script/bool_c/node.h>
#include <mu/core/segment.h>
#include <mu/script/check.h>

bool mu::script::if_c::operation::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <mu::script::bool_c::node, mu::script::operation, mu::script::operation> () (context_a));
	if (result)
	{
		auto one (boost::static_pointer_cast <mu::script::bool_c::node> (context_a.parameters (0)));
		auto two (boost::static_pointer_cast <mu::script::operation> (context_a.parameters (1)));
		auto three (boost::static_pointer_cast <mu::script::operation> (context_a.parameters (2)));
		std::vector <boost::shared_ptr <mu::core::node>> arguments;
		if (one->value)
		{
			context_a.push (two);
		}
		else
		{
			context_a.push (three);
		}
		for (auto i (context_a.parameters_begin () + 3), j (context_a.parameters_end ()); i != j; ++i)
		{
			context_a.push (*i);
		}
		result = context_a ();
	}
	return result;
}

std::wstring mu::script::if_c::operation::name ()
{
	return std::wstring (L"mu::script::if_c::operation");
}