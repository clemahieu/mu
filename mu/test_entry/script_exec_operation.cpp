#include <mu/script/exec_operation.h>
#include <mu/script/context.h>
#include <mu/script/api.h>
#include <mu/script/parser_scope_node.h>
#include <mu/script/string_node.h>
#include <mu/core/errors/error_target.h>

#include <gtest/gtest.h>

#include <gc_cpp.h>

TEST (script_test, exec1)
{
    mu::script::context context;
    auto exec (new (GC) mu::script::exec::operation);
    context.push (exec);
    auto core (mu::script::api::core ());
    context.push (core);
    context.push (new (GC) mu::script::string::node (mu::string (U"mu/source/identity.mu")));
    context.push (new (GC) mu::script::string::node (mu::string (U"op")));
    auto node1 (new (GC) mu::core::node);
    context.push (node1);
    auto valid (context ());
    ASSERT_TRUE (valid);
    ASSERT_TRUE (context.working_size () == 1);
    auto node2 (context.working (0));
    ASSERT_TRUE (node1 == node2);
}