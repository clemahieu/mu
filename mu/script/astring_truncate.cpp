#include <mu/script/astring_truncate.h>

#include <mu/script/string_node.h>
#include <mu/script/astring_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <gc_cpp.h>

bool mu::script::astring::truncate::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::string::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::string::node *> (context_a.parameters (0)));
		std::string string (one->string.begin (), one->string.end ());
		context_a.push (new (GC) mu::script::astring::node (string));
	}
	return result;
}