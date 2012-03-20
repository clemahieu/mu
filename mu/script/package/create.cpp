#include <mu/script/package/create.h>

#include <mu/script/package/node.h>
#include <mu/script/check.h>

bool mu::script::package::create::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <> () (context_a));
	if (result)
	{
		context_a.push (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
	}
	return result;
}

std::wstring mu::script::package::create::name ()
{
	return std::wstring (L"mu::script::package::create");
}