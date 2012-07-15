#include <mu/script/extensions/create.h>

#include <mu/script/extensions/node.h>
#include <mu/script/check.h>

#include <gc_cpp.h>

bool mu::script::extensions::create::operator () (mu::script::context & context_a)
{
	bool result (mu::script::check <> () (context_a));
	if (result)
	{
		context_a.push (new (GC) mu::script::extensions::node);
	}
	return result;
}