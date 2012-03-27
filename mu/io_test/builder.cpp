#include <mu/io_test/builder.h>

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

void mu::io_test::builder::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::io_test::builder::run_1 ()
{
	mu::io::ast::builder builder;
	builder (L"[:~]");
	builder ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->expressions.size () == 1);
	auto routine (cluster->expressions [0]);
	assert (routine->values.size () == 1);
	auto parameters (boost::dynamic_pointer_cast <mu::io::ast::parameters> (routine->values [0]));
	assert (parameters != nullptr);
	assert (routine->context == mu::io::debugging::context (1, 1, 0, 1, 4, 3));
}

void mu::io_test::builder::run_2 ()
{
	mu::io::ast::builder builder;
	builder (L"[:~]");
	builder (L"[:~]");
	builder ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->expressions.size () == 2);
	auto routine1 (cluster->expressions [0]);
	auto routine2 (cluster->expressions [1]);
	assert (routine1->context == mu::io::debugging::context (1, 1, 0, 1, 4, 3));
	assert (routine2->context == mu::io::debugging::context (1, 5, 4, 1, 8, 7));
}

void mu::io_test::builder::run_3 ()
{
	mu::io::ast::builder builder;
	builder (L"[[:~; a b c] a [a b c] c]");
	builder ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->expressions.size () == 1);
	auto routine (cluster->expressions [0]);
	assert (routine->context == mu::io::debugging::context (1, 1, 0, 1, 25, 24));
	assert (routine->values.size () == 4);
	auto d1 (boost::dynamic_pointer_cast <mu::io::ast::expression> (routine->values [0]));
	assert (d1.get () != nullptr);
	assert (d1->context == mu::io::debugging::context (1, 2, 1, 1, 12, 11));
	auto d2 (boost::dynamic_pointer_cast <mu::io::ast::identifier> (routine->values [1]));
	assert (d2.get () != nullptr);
	assert (d2->context == mu::io::debugging::context (1, 14, 13, 1, 14, 13));
	auto d3 (boost::dynamic_pointer_cast <mu::io::ast::expression> (routine->values [2]));
	assert (d3.get () != nullptr);
	assert (d3->context == mu::io::debugging::context (1, 16, 15, 1, 22, 21));
	auto d4 (boost::dynamic_pointer_cast <mu::io::ast::identifier> (routine->values [3]));
	assert (d4.get () != nullptr);
	assert (d4->context == mu::io::debugging::context (1, 24, 23, 1, 24, 23));
	assert (d1->values.size () == 1);
	auto d11 (boost::dynamic_pointer_cast <mu::io::ast::parameters> (d1->values [0]));
	assert (d11.get () != nullptr);
	assert (d11->context == mu::io::debugging::context (1, 3, 2, 1, 4, 3));
	assert (d1->individual_names.size () == 3);
	auto d12 (boost::dynamic_pointer_cast <mu::io::ast::identifier> (d1->individual_names [0]));
	assert (d12.get () != nullptr);
	assert (d12->context == mu::io::debugging::context (1, 7, 6, 1, 7, 6)); 
	auto d13 (boost::dynamic_pointer_cast <mu::io::ast::identifier> (d1->individual_names [1]));
	assert (d13.get () != nullptr);
	assert (d13->context == mu::io::debugging::context (1, 9, 8, 1, 9, 8));
	auto d14 (boost::dynamic_pointer_cast <mu::io::ast::identifier> (d1->individual_names [2]));
	assert (d14.get () != nullptr);
	assert (d14->context == mu::io::debugging::context (1, 11, 10, 1, 11, 10));
	assert (d3->values.size () == 3);
	auto d31 (boost::dynamic_pointer_cast <mu::io::ast::identifier> (d3->values [0]));
	assert (d31.get () != nullptr);
	assert (d31->context == mu::io::debugging::context (1, 17, 16, 1, 17, 16));
	auto d32 (boost::dynamic_pointer_cast <mu::io::ast::identifier> (d3->values [1]));
	assert (d32.get () != nullptr);
	assert (d32->context == mu::io::debugging::context (1, 19, 18, 1, 19, 18));
	auto d33 (boost::dynamic_pointer_cast <mu::io::ast::identifier> (d3->values [2]));
	assert (d33.get () != nullptr);
	assert (d33->context == mu::io::debugging::context (1, 21, 20, 1, 21, 20));
}