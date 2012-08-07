#include <mu/script/package/create.h>

#include <mu/script/package/node.h>
#include <mu/script/check.h>

#include <gc_cpp.h>

bool mu::script::package::create::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <> (context_a));
	if (result)
	{
		context_a.push (new (GC) mu::script::package::node);
	}
	return result;
}

mu::string mu::script::package::create::name ()
{
	return mu::string (U"mu::script::package::create");
}