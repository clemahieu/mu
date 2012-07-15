#include <mu/io/source.h>
#include <mu/io/ast/builder.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/core/expression.h>
#include <mu/io/ast/parameters.h>
#include <mu/core/errors/error_list.h>
#include <mu/io/ast/cluster.h>
#include <mu/io/ast/expression.h>
#include <mu/io/ast/identifier.h>

#include <boost/bind.hpp>

#include <gtest/gtest.h>

TEST (io_test, builder1)
{
	mu::io::ast::builder builder;
	builder (L"[:~]");
	builder ();
    EXPECT_EQ (builder.errors->errors.empty (), true);
	auto cluster (builder.cluster);
    EXPECT_EQ (cluster->expressions.size (), 1);
	auto routine (cluster->expressions [0]);
    EXPECT_EQ (routine->values.size (), 1);
	auto parameters (dynamic_cast <mu::io::ast::parameters *> (routine->values [0]));
    EXPECT_NE (parameters, nullptr);
    EXPECT_EQ (routine->context, mu::io::debugging::context (1, 1, 0, 1, 4, 3));
}

TEST (io_test, builder2)
{
	mu::io::ast::builder builder;
	builder (L"[:~]");
	builder (L"[:~]");
	builder ();
    EXPECT_EQ (builder.errors->errors.empty (), true);
	auto cluster (builder.cluster);
    EXPECT_EQ (cluster->expressions.size (), 2);
	auto routine1 (cluster->expressions [0]);
	auto routine2 (cluster->expressions [1]);
    EXPECT_EQ (routine1->context, mu::io::debugging::context (1, 1, 0, 1, 4, 3));
    EXPECT_EQ (routine2->context, mu::io::debugging::context (1, 5, 4, 1, 8, 7));
}

TEST (io_test, builder3)
{
	mu::io::ast::builder builder;
	builder (L"[[:~; a b c] a [a b c] c]");
	builder ();
    EXPECT_EQ (builder.errors->errors.empty (), true);
	auto cluster (builder.cluster);
    EXPECT_EQ (cluster->expressions.size (), 1);
	auto routine (cluster->expressions [0]);
    EXPECT_EQ (routine->context, mu::io::debugging::context (1, 1, 0, 1, 25, 24));
    EXPECT_EQ (routine->values.size (), 4);
	auto d1 (dynamic_cast <mu::io::ast::expression *> (routine->values [0]));
    EXPECT_NE (d1, nullptr);
    EXPECT_EQ (d1->context, mu::io::debugging::context (1, 2, 1, 1, 12, 11));
	auto d2 (dynamic_cast <mu::io::ast::identifier *> (routine->values [1]));
    EXPECT_NE (d2, nullptr);
    EXPECT_EQ (d2->context, mu::io::debugging::context (1, 14, 13, 1, 14, 13));
	auto d3 (dynamic_cast <mu::io::ast::expression *> (routine->values [2]));
    EXPECT_NE (d3, nullptr);
    EXPECT_EQ (d3->context, mu::io::debugging::context (1, 16, 15, 1, 22, 21));
	auto d4 (dynamic_cast <mu::io::ast::identifier *> (routine->values [3]));
    EXPECT_NE (d4, nullptr);
    EXPECT_EQ (d4->context, mu::io::debugging::context (1, 24, 23, 1, 24, 23));
    EXPECT_EQ (d1->values.size (), 1);
	auto d11 (dynamic_cast <mu::io::ast::parameters *> (d1->values [0]));
    EXPECT_NE (d11, nullptr);
    EXPECT_EQ (d11->context, mu::io::debugging::context (1, 3, 2, 1, 4, 3));
    EXPECT_EQ (d1->individual_names.size (), 3);
	auto d12 (dynamic_cast <mu::io::ast::identifier *> (d1->individual_names [0]));
    EXPECT_NE (d12, nullptr);
    EXPECT_EQ (d12->context, mu::io::debugging::context (1, 7, 6, 1, 7, 6));
	auto d13 (dynamic_cast <mu::io::ast::identifier *> (d1->individual_names [1]));
    EXPECT_NE (d13, nullptr);
    EXPECT_EQ (d13->context, mu::io::debugging::context (1, 9, 8, 1, 9, 8));
	auto d14 (dynamic_cast <mu::io::ast::identifier *> (d1->individual_names [2]));
    EXPECT_NE (d14, nullptr);
    EXPECT_EQ (d14->context, mu::io::debugging::context (1, 11, 10, 1, 11, 10));
    EXPECT_EQ (d3->values.size (), 3);
	auto d31 (dynamic_cast <mu::io::ast::identifier *> (d3->values [0]));
    EXPECT_NE (d31, nullptr);
    EXPECT_EQ (d31->context, mu::io::debugging::context (1, 17, 16, 1, 17, 16));
	auto d32 (dynamic_cast <mu::io::ast::identifier *> (d3->values [1]));
    EXPECT_NE (d32, nullptr);
    EXPECT_EQ (d32->context, mu::io::debugging::context (1, 19, 18, 1, 19, 18));
	auto d33 (dynamic_cast <mu::io::ast::identifier *> (d3->values [2]));
    EXPECT_NE (d33, nullptr);
    EXPECT_EQ (d33->context, mu::io::debugging::context (1, 21, 20, 1, 21, 20));
}
