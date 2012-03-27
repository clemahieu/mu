#include <mu/script_test/debugging/trace_target.h>

#include <mu/script/debugging/trace_target.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/builder.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/fail/operation.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/source.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/values/operation.h>
#include <mu/io/debugging/mapping.h>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

#include <sstream>

void mu::script_test::debugging::trace_target::run ()
{
	run_1 ();
}

void mu::script_test::debugging::trace_target::run_1 ()
{
	mu::script::context context;
	mu::core::errors::errors errors (boost::make_shared <mu::script::debugging::trace_target> (boost::make_shared <mu::core::errors::error_list> (), context, boost::make_shared <mu::io::debugging::mapping> ()));
	context.errors = errors;
	mu::script::builder builder;
	builder.analyzer.extensions->extensions_m [L"fail"] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::fail::operation> ());
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[fail]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	context.push (routine);
	auto valid (context ());
	assert (!valid);
	assert (context.working_size () == 0);
	std::wstringstream message;
	errors.print (message);
	std::wstring mess (message.str ());
}