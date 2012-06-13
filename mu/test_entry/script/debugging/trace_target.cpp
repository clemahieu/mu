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

#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

#include <sstream>

#include <gtest/gtest.h>

TEST (script_test, trace_target1)
{
	mu::script::context context;
	mu::core::errors::errors errors (boost::make_shared <mu::script::debugging::trace_target> (boost::make_shared <mu::core::errors::error_list> (), context));
	context.errors = errors;
	mu::script::builder builder;
	builder.analyzer.extensions->extensions_m [L"fail"] = boost::make_shared <mu::io::analyzer::extensions::global> (boost::make_shared <mu::script::fail::operation> ());
	builder (L"[fail]");
	builder ();
	EXPECT_EQ (builder.errors->errors.empty (), true);
	auto cluster (builder.cluster);
	EXPECT_EQ (cluster->routines.size (), 1);
	auto routine (cluster->routines [0]);
	context.push (routine);
	auto valid (context ());
	EXPECT_EQ (!valid, false);
	EXPECT_EQ (context.working_size (), 0);
	std::wstringstream message;
	errors.print (message);
	std::wstring mess (message.str ());
}