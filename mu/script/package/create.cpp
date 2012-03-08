#include "create.h"

#include <mu/script/package/node.h>

void mu::script::package::create::operator () (mu::script::context & context_a)
{
	context_a.results.push_back (boost::shared_ptr <mu::script::package::node> (new mu::script::package::node));
}

std::wstring mu::script::package::create::name ()
{
	return std::wstring (L"mu::script::package::create");
}

size_t mu::script::package::create::count ()
{
	return 0;
}