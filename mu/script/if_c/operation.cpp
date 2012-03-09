#include "operation.h"

#include <mu/script/bool_c/node.h>
#include <mu/core/segment.h>

void mu::script::if_c::operation::operator () (mu::script::context & context_a)
{
	auto one (boost::dynamic_pointer_cast <mu::script::bool_c::node> (context_a.parameters [0]));
	auto two (boost::dynamic_pointer_cast <mu::script::fixed> (context_a.parameters [1]));
	auto three (boost::dynamic_pointer_cast <mu::script::fixed> (context_a.parameters [2]));
	if (one.get () != nullptr)
	{
		if (two.get () != nullptr)
		{
			if (three.get () != nullptr)
			{
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
			else
			{
				invalid_type (context_a.errors, context_a.parameters [2], 2);
			}
		}
		else
		{
			invalid_type (context_a.errors, context_a.parameters [1], 1);
		}
	}
	else
	{
		invalid_type (context_a.errors, context_a.parameters [0], 0);
	}
}

size_t mu::script::if_c::operation::count ()
{
	return 3;
}

std::wstring mu::script::if_c::operation::name ()
{
	return std::wstring (L"mu::script::if_c::operation");
}