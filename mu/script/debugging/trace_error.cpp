#include <mu/script/debugging/trace_error.h>

#include <mu/script/values/operation.h>
#include <mu/script/string/node.h>

mu::script::debugging::trace_error::trace_error (boost::shared_ptr <mu::script::values::operation> trace_a, boost::shared_ptr <mu::core::errors::error> error_a)
	: trace (trace_a),
	error (error_a)
{
}

void mu::script::debugging::trace_error::string (std::wostream & stream)
{
	error->string (stream);
	stream << L'\n';
	for (auto i (trace->values.begin ()), j (trace->values.end ()); i != j; ++i)
	{
		assert (boost::dynamic_pointer_cast <mu::script::string::node> (*i));
		auto string (boost::static_pointer_cast <mu::script::string::node> (*i));
		stream << string->string;
		stream << L'\n';
	}
}