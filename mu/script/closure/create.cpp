#include "create.h"

#include <mu/script/closure/operation.h>
#include <mu/script/integer/node.h>
#include <mu/script/check.h>

void mu::script::closure::create::operator () (mu::script::context & context_a)
{
	if (mu::script::check <mu::script::operation, mu::script::integer::node> () (context_a))
	{
		auto operation (boost::static_pointer_cast <mu::script::operation> (context_a.parameters [0]));
		auto count (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters [1]));
		context_a.results.push_back (boost::shared_ptr <mu::core::node> (new mu::script::closure::operation (count->value, operation)));
	}
}

std::wstring mu::script::closure::create::name ()
{
	return std::wstring (L"mu::script::closure::create");
}