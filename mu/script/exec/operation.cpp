#include <mu/script/exec/operation.h>

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/io/source.h>
#include <mu/script/loads/operation.h>
#include <mu/script/extensions/node.h>
#include <mu/script/run/operation.h>
#include <mu/script/context.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <sstream>

mu::script::exec::operation::operation (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: extensions (extensions_a)
{
}

bool mu::script::exec::operation::operator () (mu::script::context & context_a)
{
	bool result (true);
	if (context_a.parameters_size () > 0)
	{
		context_a.push (boost::make_shared <mu::script::run::operation> ());
		context_a.push (boost::make_shared <mu::script::extensions::node> (extensions));
		for (auto i (context_a.parameters_begin ()), j (context_a.parameters_end ()); i != j; ++i)
		{
			context_a.push (*i);
		}
		result = context_a ();
	}
	else
	{
		std::wstringstream message;
		message << L"Operation ";
		message << name ();
		message << L" requires at least one argument";
		context_a.errors (message.str ());
		result = false;
	}
	return result;
}

std::wstring mu::script::exec::operation::name ()
{
	return std::wstring (L"mu::script::exec::operation");
}