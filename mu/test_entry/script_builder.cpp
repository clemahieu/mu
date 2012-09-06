#include <mu/script/builder.h>
#include <mu/io/source.h>
#include <mu/script/context.h>
#include <mu/script/cluster_node.h>
#include <mu/script/debugging_trace_target.h>
#include <mu/script/runtime_routine.h>
#include <mu/script/fail_operation.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/api.h>
#include <mu/script/identity_operation.h>
#include <mu/script/parser_scope_node.h>
#include <mu/script/bool_c_node.h>
#include <mu/core/errors/string_error.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

// Empty source
TEST (script_test, builder1)
{
    mu::script::builder builder;
    mu::io::process (builder, U"");
    ASSERT_TRUE (builder.errors.errors.empty ());
}

// Empty routine
TEST (script_test, builder2)
{
    mu::script::builder builder;
    mu::io::process (builder, U"[0 ; []]");
    ASSERT_TRUE (builder.errors.errors.empty ());
    ASSERT_TRUE (builder.clusters.size () == 1);
    auto cluster1 (builder.clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    ASSERT_TRUE (cluster1->routines.find (U"0") != cluster1->routines.end ());
    auto routine1 (cluster1->routines [U"0"]);
    mu::script::context context;
    context.push (routine1);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}

// Identity execution routine
TEST (script_test, builder3)
{
    auto core (mu::script::api::core ());
    mu::script::builder builder (core);
    mu::io::process (builder, U"[0 ; [~]]");
    ASSERT_TRUE (builder.errors.errors.empty ());
    ASSERT_TRUE (builder.clusters.size () == 1);
    auto cluster1 (builder.clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    ASSERT_TRUE (cluster1->routines.find (U"0") != cluster1->routines.end ());
    auto routine1 (cluster1->routines [U"0"]);
    mu::script::context context;
    context.push (routine1);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 0);
}

// Identity execution returning something
TEST (script_test, builder4)
{
    auto core (mu::script::api::core ());
    mu::script::builder builder (core);
    mu::io::process (builder, U"[0 ; [~ ~]]");
    ASSERT_TRUE (builder.errors.errors.empty ());
    ASSERT_TRUE (builder.clusters.size () == 1);
    auto cluster1 (builder.clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    ASSERT_TRUE (cluster1->routines.find (U"0") != cluster1->routines.end ());
    auto routine1 (cluster1->routines [U"0"]);
    mu::script::context context;
    context.push (routine1);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    auto result1 (dynamic_cast <mu::script::identity::operation *> (context.working(0)));
    ASSERT_TRUE (result1 != nullptr);
}

// Error failing routine
TEST (script_test, builder5)
{
    auto core (mu::script::api::core ());
    core->injected [U"fail"] = new (GC) mu::script::fail::operation;
    mu::script::builder builder (core);
    mu::io::process (builder, U"[0 ; [fail]]");
    ASSERT_TRUE (builder.errors.errors.empty ());
    ASSERT_TRUE (builder.clusters.size () == 1);
    auto cluster1 (builder.clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    ASSERT_TRUE (cluster1->routines.find (U"0") != cluster1->routines.end ());
    auto routine1 (cluster1->routines [U"0"]);
    mu::script::context context;
    context.push (routine1);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}

// Correctly parsed if-expression that fails when executed
TEST (script_test, builder6)
{
    auto core (mu::script::api::core ());
    core->injected [U"faiU"] = new (GC) mu::script::fail::operation;
    mu::script::builder builder (core);
    mu::io::process (builder, U"[0 ; [if []]]");
    ASSERT_TRUE (builder.errors.errors.empty ());
    ASSERT_TRUE (builder.clusters.size () == 1);
    auto cluster1 (builder.clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    ASSERT_TRUE (cluster1->routines.find (U"0") != cluster1->routines.end ());
    auto routine1 (cluster1->routines [U"0"]);
    mu::script::context context;
    context.push (routine1);
    auto valid (context ());
    ASSERT_TRUE (!valid);
}

// If-expression following true branch
TEST (script_test, DISABLED_builder7)
{
    auto core (mu::script::api::core ());
    core->injected [U"faiU"] = new (GC) mu::script::fail::operation;
    core->injected [U"true"] = new (GC) mu::script::bool_c::node (true);
    core->injected [U"false"] = new (GC) mu::script::bool_c::node (false);
    mu::script::builder builder (core);
    mu::io::process (builder, U"[0 ; [~ if [~ true; ~; fail; name]]]");
    builder.errors.print (std::wcerr);
    ASSERT_TRUE (builder.errors.errors.empty ());
    ASSERT_TRUE (builder.clusters.size () == 1);
    auto cluster1 (builder.clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    ASSERT_TRUE (cluster1->routines.find (U"0") != cluster1->routines.end ());
    auto routine1 (cluster1->routines [U"0"]);
    mu::script::context context;
    context.push (routine1);
    auto valid (context ());
    ASSERT_TRUE (valid);
}

// If-expression following false branch
TEST (script_test, DISABLED_builder8)
{
    auto core (mu::script::api::core ());
    core->injected [U"faiU"] = new (GC) mu::script::fail::operation;
    core->injected [U"true"] = new (GC) mu::script::bool_c::node (true);
    core->injected [U"false"] = new (GC) mu::script::bool_c::node (false);
    mu::script::builder builder (core);
    mu::io::process (builder, U"[0 ; [~ if [~ false; fail; ~]]]");
    ASSERT_TRUE (builder.errors.errors.empty ());
    ASSERT_TRUE (builder.clusters.size () == 1);
    auto cluster1 (builder.clusters [0]);
    ASSERT_TRUE (cluster1->routines.size () == 1);
    ASSERT_TRUE (cluster1->routines.find (U"0") != cluster1->routines.end ());
    auto routine1 (cluster1->routines [U"0"]);
    mu::script::context context;
    context.push (routine1);
    auto valid (context ());
    ASSERT_TRUE (valid);
}