#include <gtest/gtest.h>

#include <mu/script/context.h>
#include <mu/script/abort_operation.h>

TEST (script_test, abort1)
{
    mu::script::context context;
    mu::script::abort::operation operation;
    context.push (&operation);
    ASSERT_DEATH (context (), "");
}