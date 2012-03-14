#include <mu/script_io_test/lambda.h>

#include <mu/script_io/builder.h>
#include <mu/script/runtime/routine.h>
#include <mu/script/integer/node.h>
#include <mu/script/cluster/node.h>
#include <mu/io/debugging/error.h>

#include <boost/bind.hpp>

void mu::script_io_test::lambda::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void mu::script_io_test::lambda::run_1 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>[[~ # d42]]]");
	source ();
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	assert (builder.errors->errors.empty ());
	auto routine (cluster->routines [0]);
}

void mu::script_io_test::lambda::run_2 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>[[]]]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
}

void mu::script_io_test::lambda::run_3 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=> thing]");
	source ();
	assert (builder.clusters.empty ());
	assert (!builder.errors->errors.empty ());
	auto e1 (boost::dynamic_pointer_cast <mu::io::debugging::error> (builder.errors->errors [0]));
	assert (e1.get () != nullptr);
	assert (e1->context == mu::core::context (1, 2, 1, 1, 9, 8));
}

void mu::script_io_test::lambda::run_4 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>]");
	source ();
	assert (builder.clusters.empty ());
	assert (!builder.errors->errors.empty ());
	auto e1 (boost::dynamic_pointer_cast <mu::io::debugging::error> (builder.errors->errors [0]));
	assert (e1.get () != nullptr);
	assert (e1->context == mu::core::context (1, 2, 1, 1, 3, 2));
}

void mu::script_io_test::lambda::run_5 ()
{
	mu::script_io::builder builder;
	mu::io::source source (boost::bind (&mu::io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>[]]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
}