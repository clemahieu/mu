#include "create.h"

#include <mu/script/closure/operation.h>
#include <mu/script/integer/node.h>

void mu::script::closure::create::operator () (mu::script::context & context_a)
{
	auto operation (boost::dynamic_pointer_cast <mu::script::operation> (context_a.parameters [0]));
	auto count (boost::dynamic_pointer_cast <mu::script::integer::node> (context_a.parameters [1]));
	if (operation.get () != nullptr)
	{
		if (count.get () != nullptr)
		{
			context_a.results.push_back (boost::shared_ptr <mu::core::node> (new mu::script::closure::operation (count->value, operation)));
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

size_t mu::script::closure::create::count ()
{
	return 2;
}

std::wstring mu::script::closure::create::name ()
{
	return std::wstring (L"mu::script::closure::create");
}