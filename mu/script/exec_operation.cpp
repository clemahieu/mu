#include <mu/script/exec_operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string_node.h>
#include <mu/io/lexer_istream_input.h>
#include <mu/io/source.h>
#include <mu/script/loads_operation.h>
#include <mu/script/parser_scope_node.h>
#include <mu/script/run_operation.h>
#include <mu/script/context.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>

#include <sstream>

#include <gc_cpp.h>

mu::script::exec::operation::operation (mu::io::keywording::extensions * extensions_a):
extensions (extensions_a)
{
}

bool mu::script::exec::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		context_a.push (new (GC) mu::script::run::operation);
		context_a.push (new (GC) mu::script::parser_scope::node (extensions));
		for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
		{
			context_a.push (*i);
		}
		result = context_a ();
	}
	else
	{
		mu::stringstream message;
		message << L"Operation ";
		message << name ();
		message << L" requires at least one argument";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}

mu::string mu::script::exec::operation::name ()
{
	return mu::string (U"mu::script::exec::operation");
}