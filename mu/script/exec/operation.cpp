#include "operation.h"

#include <mu/core/errors/error_target.h>
#include <mu/script/string/node.h>
#include <mu/io/lexer/istream_input.h>
#include <mu/script_io/builder.h>
#include <mu/io/source.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/cluster/node.h>
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

void mu::script::exec::operation::operator () (mu::script::context & context_a)
{
	if (context_a.parameters.size () > 0)
	{
		std::vector <boost::shared_ptr <mu::core::node>> a1;
		a1.push_back (boost::make_shared <mu::script::extensions::node> (extensions));
		a1.insert (a1.end (), context_a.parameters.begin (), context_a.parameters.end ());
		mu::script::run::operation run;
        auto ctx (mu::script::context (context_a.errors, a1, context_a.results));
		run (ctx);
	}
	else
	{
		std::wstringstream message;
		message << L"Operation ";
		message << name ();
		message << L" requires at least one argument";
		(*context_a.errors) (message.str ());
	}
}

std::wstring mu::script::exec::operation::name ()
{
	return std::wstring (L"mu::script::exec::operation");
}