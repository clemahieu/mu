#include <mu/script/debugging/trace_error.h>

#include <mu/script/values/operation.h>
#include <mu/script/string/node.h>

mu::script::debugging::trace_error::trace_error (mu::script::values::operation * trace_a, mu::core::errors::error * error_a)
	: trace (trace_a),
	error (error_a)
{
}

void mu::script::debugging::trace_error::string (mu::ostream & stream)
{
	error->string (stream);
	stream << L'\n';
	for (auto i (trace->values.begin ()), j (trace->values.end ()); i != j; ++i)
	{
		assert (dynamic_cast <mu::script::string::node *> (*i));
		auto string (static_cast <mu::script::string::node *> (*i));
		stream << string->string;
		stream << L'\n';
	}
}