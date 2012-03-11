#include <mu/script/runtime/stacktrace_error.h>

#include <mu/script/context.h>

#include <iostream>

mu::script::runtime::stacktrace_error::stacktrace_error (mu::script::context & context_a, boost::shared_ptr <mu::core::errors::error> error_a)
	: error (error_a),
	stack (context_a.stack)
{
}

mu::core::errors::error_id mu::script::runtime::stacktrace_error::error_type ()
{
	return mu::core::errors::error_stacktrace_error;
}

void mu::script::runtime::stacktrace_error::string (std::wostream & stream)
{
	error->string (stream);
	stream<< L"\n";
	for (auto i (stack.begin ()), j (stack.end ()); i != j; ++i)
	{
		stream << (*i)->name ();
		stream << L"\n";
	}
}