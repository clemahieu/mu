#include <mu/script/runtime/stacktrace_error.h>

#include <iostream>

mu::script::runtime::stacktrace_error::stacktrace_error (std::vector <std::type_info const *> & types_a, boost::shared_ptr <mu::core::errors::error> error_a)
	: error (error_a)
{
	for (auto i (types_a.begin ()), j (types_a.end ()); i != j; ++i)
	{
		std::string name ((*i)->name ());
		types.push_back (std::wstring (name.begin (), name.end ()));
	}
}

mu::core::errors::error_id mu::script::runtime::stacktrace_error::error_type ()
{
	return mu::core::errors::error_stacktrace_error;
}

void mu::script::runtime::stacktrace_error::string (std::wostream & stream)
{
	error->string (stream);
	stream<< L"\n";
	for (auto i (types.begin ()), j (types.end ()); i != j; ++i)
	{
		stream << *i;
		stream << L"\n";
	}
}