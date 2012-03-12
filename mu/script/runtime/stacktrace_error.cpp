#include <mu/script/runtime/stacktrace_error.h>

#include <mu/script/context.h>
#include <mu/script/debugging/mapping.h>
#include <mu/script/debugging/operation_info.h>

#include <iostream>

mu::script::runtime::stacktrace_error::stacktrace_error (mu::script::context & context_a, mu::script::debugging::mapping & mapping_a, boost::shared_ptr <mu::core::errors::error> error_a)
	: error (error_a)
{
	for (auto i (context_a.function_stack.begin ()), j (context_a.function_stack.end ()); i != j; ++i)
	{
		stack.push_back (mapping_a.operation_info (*i)->stacktrace_line ());
	}
}

mu::core::errors::error_id mu::script::runtime::stacktrace_error::error_type ()
{
	return mu::core::errors::error_stacktrace_error;
}

void mu::script::runtime::stacktrace_error::string (std::wostream & stream)
{
	error->string (stream);
	stream << L"\n";
	for (auto i (stack.begin ()), j (stack.end ()); i != j; ++i)
	{
		stream << *i;
		stream << L"\n";
	}
}