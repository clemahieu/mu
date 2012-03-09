#include "operation.h"

#include <mu/script/bool_c/node.h>
#include <mu/core/segment.h>
#include <mu/script/check.h>

void mu::script::if_c::operation::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::bool_c::node, mu::script::operation, mu::script::operation> () (context_a))
	{
		auto one (boost::static_pointer_cast <mu::script::bool_c::node> (context_a.parameters [0]));
		auto two (boost::static_pointer_cast <mu::script::operation> (context_a.parameters [1]));
		auto three (boost::static_pointer_cast <mu::script::operation> (context_a.parameters [2]));
		std::vector <boost::shared_ptr <mu::core::node>> arguments;
		if (one->value)
		{
            auto ctx (mu::script::context (context_a.errors, arguments, context_a.results));
			(*two) (ctx);
		}
		else
		{
            auto ctx (mu::script::context (context_a.errors, arguments, context_a.results));
			(*three) (ctx);
		}
	}
}

std::wstring mu::script::if_c::operation::name ()
{
	return std::wstring (L"mu::script::if_c::operation");
}