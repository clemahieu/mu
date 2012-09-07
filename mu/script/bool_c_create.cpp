#include <mu/script/bool_c_create.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string_node.h>
#include <mu/script/bool_c_node.h>
#include <mu/core/check.h>
#include <mu/script/context.h>

#include <sstream>
#include <algorithm>

#include <gc_cpp.h>

mu::script::bool_c::create::create ()
{
	values [mu::string (U"true")] = new (GC) mu::script::bool_c::node (true);
	values [mu::string (U"false")] = new (GC) mu::script::bool_c::node (false);
	values [mu::string (U"yes")] = new (GC) mu::script::bool_c::node (true);
	values [mu::string (U"no")] = new (GC) mu::script::bool_c::node (false);
	values [mu::string (U"1")] = new (GC) mu::script::bool_c::node (true);
	values [mu::string (U"0")] = new (GC) mu::script::bool_c::node (false);
	values [mu::string (U"on")] = new (GC) mu::script::bool_c::node (true);
	values [mu::string (U"off")] = new (GC) mu::script::bool_c::node (false);
	values [mu::string (U"high")] = new (GC) mu::script::bool_c::node (true);
	values [mu::string (U"low")] = new (GC) mu::script::bool_c::node (false);
}

bool mu::script::bool_c::create::operator () (mu::script::context & context_a)
{
	bool result (mu::core::check <mu::script::string::node> (context_a));
	if (result)
	{
		auto one (static_cast <mu::script::string::node *> (context_a.parameters (0)));
		mu::string lower;
		std::transform (one->string.begin (), one->string.end (), lower.begin (), ::tolower);
		auto existing (values.find (lower));
		if (existing != values.end ())
		{
			context_a.push (existing->second);
		}
		else
		{
			mu::stringstream message;
			message << U"Cannot convert value: ";
			message << one->string;
			message << U" to a bool";
			context_a.errors (message.str ());
			result = false;
		}
	}
	return result;
}