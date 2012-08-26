#include <mu/script/extensions_create.h>

#include <mu/script/extensions_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::script::extensions::create::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <> (context_a));
	if (result)
	{
		context_a.push (new (GC) mu::script::extensions::node);
	}
	return result;
}