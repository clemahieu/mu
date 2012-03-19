#include <mu/script/closure/create.h>

#include <mu/script/closure/operation.h>
#include <mu/script/integer/node.h>
#include <mu/script/check.h>

bool mu::script::closure::create::operator () (mu::script_runtime::context & context_a)
{
	bool result (mu::script::check <mu::script_runtime::operation, mu::script::integer::node> () (context_a));
	if (result)
	{
		auto operation (boost::static_pointer_cast <mu::script_runtime::operation> (context_a.parameters (0)));
		auto count (boost::static_pointer_cast <mu::script::integer::node> (context_a.parameters (1)));
		context_a.push (boost::shared_ptr <mu::core::node> (new mu::script::closure::operation (count->value, operation)));
	}
	return result;
}

std::wstring mu::script::closure::create::name ()
{
	return std::wstring (L"mu::script::closure::create");
}