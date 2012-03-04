#include <mu/script/exec.operation.h>

#include <mu/core/errors.error_target.h>
#include <mu/script/string.node.h>
#include <mu/io/lexer.istream_input.h>
#include <mu/script_io/builder.h>
#include <mu/io/source.h>
#include <mu/script/runtime.routine.h>
#include <mu/script/cluster.node.h>
#include <mu/script/loads.operation.h>
#include <mu/script/extensions.node.h>
#include <mu/script/run.operation.h>

#include <boost/filesystem.hpp>
#include <boost/bind.hpp>
#include <boost/make_shared.hpp>

#include <sstream>

mu::script::exec::operation::operation (boost::shared_ptr <mu::io::analyzer::extensions::extensions> extensions_a)
	: extensions (extensions_a)
{
}

void mu::script::exec::operation::perform (boost::shared_ptr <mu::core::errors::error_target> errors_a, mu::core::segment <boost::shared_ptr <mu::core::node>> parameters, std::vector <boost::shared_ptr <mu::core::node>> & results)
{
	if (parameters.size () > 0)
	{
		std::vector <boost::shared_ptr <mu::core::node>> a1;
		a1.push_back (boost::make_shared <mu::script::extensions::node> (extensions));
		a1.insert (a1.end (), parameters.begin (), parameters.end ());
		mu::script::run::operation run;
		run.perform (errors_a, a1, results);
	}
	else
	{
		std::wstringstream message;
		message << L"Operation ";
		message << name ();
		message << L" requires at least one argument";
		(*errors_a) (message.str ());
	}
}

std::wstring mu::script::exec::operation::name ()
{
	return std::wstring (L"mu::script::exec::operation");
}
