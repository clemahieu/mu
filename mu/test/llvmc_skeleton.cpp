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

TEST (llvmc_analyzer, function_type_name)
{
	mu::llvmc::skeleton::function function (mu::empty_region);
	mu::llvmc::skeleton::function_type function_type (&function);
	auto name (function_type.name ());
	ASSERT_EQ (U"function [] []", name);
}

TEST (llvmc_analyzer, function_type_name2)
{
	mu::llvmc::skeleton::function function (mu::empty_region);
	mu::llvmc::skeleton::function_type function_type (&function);
	mu::llvmc::skeleton::integer_type type1 (8);
	mu::llvmc::skeleton::parameter parameter1 (mu::empty_region, function.entry, &type1, U"p0");
	function.parameters.push_back (&parameter1);
	mu::llvmc::skeleton::parameter parameter2 (mu::empty_region, function.entry, &type1, U"p1");
	function.parameters.push_back (&parameter2);
	auto name (function_type.name ());
	ASSERT_EQ (U"function [int8 int8] []", name);
}

TEST (llvmc_analyzer, function_type_name3)
{
	mu::llvmc::skeleton::function function (mu::empty_region);
	mu::llvmc::skeleton::function_type function_type (&function);
	mu::llvmc::skeleton::integer_type type1 (8);
	mu::llvmc::skeleton::constant_integer constant1 (mu::empty_region, &type1, 42);
	mu::llvmc::skeleton::result result1 (&type1, &constant1);
	mu::llvmc::skeleton::result result2 (&type1, &constant1);
    function.results = {{{&result1, &result2}, {}}};
	auto name (function_type.name ());
	ASSERT_EQ (U"function [] [[int8 int8]]", name);
}

TEST (llvmc_analyzer, function_type_name4)
{
	mu::llvmc::skeleton::function function (mu::empty_region);
	mu::llvmc::skeleton::function_type function_type (&function);
	mu::llvmc::skeleton::integer_type type1 (8);
	mu::llvmc::skeleton::constant_integer constant1 (mu::empty_region, &type1, 42);
	mu::llvmc::skeleton::result result1 (&type1, &constant1);
    function.results = {{{&result1}, {&constant1}}};
	auto name (function_type.name ());
	ASSERT_EQ (U"function [] [[int8]]", name);
}

TEST (llvmc_analyzer, function_type_name5)
{
	mu::llvmc::skeleton::function function (mu::empty_region);
	mu::llvmc::skeleton::function_type function_type (&function);
	mu::llvmc::skeleton::integer_type type1 (8);
	mu::llvmc::skeleton::constant_integer constant1 (mu::empty_region, &type1, 42);
	mu::llvmc::skeleton::result result1 (&type1, &constant1);
	mu::llvmc::skeleton::result result2 (&type1, &constant1);
    function.results = {{{&result1}, {}}, {{&result2}, {}}};
	auto name (function_type.name ());
	ASSERT_EQ (U"function [] [[int8][int8]]", name);
}

TEST (llvmc_analyzer, fixed_array_type)
{
	mu::llvmc::skeleton::integer_type type1 (8);
	mu::llvmc::skeleton::fixed_array_type farray (&type1, 4);
	auto name (farray.name ());
	ASSERT_EQ (U"farray int8 #4", name);
}

TEST (llvmc_analyzer, unit_type)
{
	mu::llvmc::skeleton::unit_type type1;
	auto name (type1.name ());
	ASSERT_EQ (U"unit", name);
}

TEST (llvmc_analyzer, pointer_type)
{
	mu::llvmc::skeleton::integer_type type1 (8);
	mu::llvmc::skeleton::pointer_type type2 (&type1);
	auto name (type2.name ());
	ASSERT_EQ (U"ptr int8", name);
}

TEST (llvmc_analyzer, number_bits_0)
{
    mu::llvmc::skeleton::number number1 (0);
    auto bits (number1.bits_required ());
    ASSERT_EQ (1, bits);
}

TEST (llvmc_analyzer, number_bits_1)
{
    mu::llvmc::skeleton::number number1 (1);
    auto bits (number1.bits_required ());
    ASSERT_EQ (1, bits);
}

TEST (llvmc_analyzer, number_bits_255)
{
    mu::llvmc::skeleton::number number1 (255);
    auto bits (number1.bits_required ());
    ASSERT_EQ (8, bits);
}

TEST (llvmc_analyzer, number_bits_256)
{
    mu::llvmc::skeleton::number number1 (256);
    auto bits (number1.bits_required ());
    ASSERT_EQ (9, bits);
}