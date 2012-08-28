#include <mu/script/parser_scope_create.h>

#include <mu/script/parser_scope_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::script::parser_scope::create::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <> (context_a));
	if (result)
	{
		context_a.push (new (GC) mu::script::parser_scope::node);
	}
	return result;
}