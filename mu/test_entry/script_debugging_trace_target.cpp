#include <mu/script/debugging_trace_target.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/builder.h>
#include <mu/script/fail_operation.h>
#include <mu/io/source.h>
#include <mu/script/cluster_node.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/values_operation.h>
#include <mu/io/analyzer_extensions.h>

#include <boost/bind.hpp>

#include <sstream>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, trace_target1)
{
	mu::script::context context (*new (GC) mu::script::debugging::trace_target (new (GC) mu::core::errors::error_list, context));
	mu::script::builder builder;
	(*builder.analyzer.extensions) (mu::string (U"fail"), new (GC) mu::script::fail::operation);
	mu::io::process (builder, U"[1 ; [fail]]");
	builder.errors.print (std::wcerr);
	ASSERT_TRUE (builder.errors.errors.empty ());
    ASSERT_TRUE (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	ASSERT_TRUE (cluster->routines.size () == 1);
	auto routine (cluster->routines [mu::string (U"1")]);
	context.push (routine);
	auto valid (context ());
	EXPECT_EQ (!valid, true);
	EXPECT_EQ (context.working_size (), 0);
}