#include <gtest/gtest.h>

#include <mu/llvmc/skeleton.hpp>
#include <mu/core/error.hpp>

TEST (llvmc_skeleton, most_specific_branch1)
{
    mu::llvmc::skeleton::branch branch1 (nullptr);
    mu::llvmc::skeleton::branch branch2 (nullptr);
    auto branch3 (branch1.most_specific (&branch2));
    ASSERT_EQ (nullptr, branch3);
}

TEST (llvmc_skeleton, most_specific_branch2)
{
    mu::llvmc::skeleton::branch branch1 (nullptr);
    mu::llvmc::skeleton::branch branch2 (&branch1);
    auto branch3 (branch1.most_specific (&branch2));
    ASSERT_EQ (&branch2, branch3);
}

TEST (llvmc_skeleton, most_specific_branch3)
{
    mu::llvmc::skeleton::branch branch1 (nullptr);
    mu::llvmc::skeleton::branch branch2 (&branch1);
    auto branch3 (branch2.most_specific (&branch1));
    ASSERT_EQ (&branch2, branch3);
}

TEST (llvmc_skeleton, most_specific_branch4)
{
    mu::llvmc::skeleton::branch branch1 (nullptr);
    mu::llvmc::skeleton::branch branch2 (&branch1);
    mu::llvmc::skeleton::branch branch3 (&branch1);
    auto branch4 (branch2.most_specific (&branch3));
    ASSERT_EQ (nullptr, branch4);
}

TEST (llvmc_analyzer, ptr_equality)
{
    mu::llvmc::skeleton::integer_type type1 (8);
    mu::llvmc::skeleton::pointer_type type2 (&type1);
    mu::llvmc::skeleton::integer_type type3 (8);
    mu::llvmc::skeleton::pointer_type type4 (&type3);
    ASSERT_EQ (type2, type4);
}

TEST (llvmc_analyzer, error_integer_type_match_pointer)
{
    mu::llvmc::skeleton::integer_type type1 (8);
    mu::llvmc::skeleton::integer_type type3 (8);
    mu::llvmc::skeleton::pointer_type type4 (&type3);
    ASSERT_NE (type1, type4);
}