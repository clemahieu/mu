#include <mu/script_test/debugging/trace_types.h>

#include <mu/script/context.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/debugging/trace_types.h>
#include <mu/script/values/operation.h>
#include <mu/script/builder.h>
#include <mu/io/source.h>
#include <mu/io/analyzer/extensions/extensions.h>
#include <mu/io/analyzer/extensions/global.h>
#include <mu/script/cluster/node.h>
#include <mu/script/runtime/routine.h>

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

void mu::script_test::debugging::trace_types::run ()
{
	run_1 ();
	run_2 ();
}

void mu::script_test::debugging::trace_types::run_1 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	context.push (boost::make_shared <mu::script::debugging::trace_types> ());
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 1);
	auto operation (boost::dynamic_pointer_cast <mu::script::values::operation> (context.working (0)));
	assert (operation != nullptr);
	assert (operation->values.size () == 1);
}

void mu::script_test::debugging::trace_types::run_2 ()
{
	mu::core::errors::errors errors (boost::make_shared <mu::core::errors::error_list> ());
	mu::script::context context (errors);
	mu::script::builder builder;
	builder.analyzer.extensions->extensions_m [L"trace"] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::debugging::trace_types> ());
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[trace]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	context.push (routine);
	auto valid (context ());
	assert (valid);
	assert (context.working_size () == 1);
	auto trace (boost::dynamic_pointer_cast <mu::script::values::operation> (context.working (0)));
	assert (trace != nullptr);
}