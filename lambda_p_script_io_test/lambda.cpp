#include "lambda.h"

#include <lambda_p_script_io/builder.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/integer/node.h>
#include <lambda_p_script/cluster/node.h>

#include <boost/bind.hpp>

void lambda_p_script_io_test::lambda::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void lambda_p_script_io_test::lambda::run_1 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>[[~ # d42]]]");
	source ();
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	assert (builder.errors->errors.empty ());
	auto routine (cluster->routines [0]);
}

void lambda_p_script_io_test::lambda::run_2 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>[[]]]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
}

void lambda_p_script_io_test::lambda::run_3 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=> thing]");
	source ();
	assert (builder.clusters.empty ());
	assert (!builder.errors->errors.empty ());
	auto e1 (builder.errors->errors [0]);
	assert (e1.second == lambda_p::context (1, 2, 1, 1, 9, 8));
}

void lambda_p_script_io_test::lambda::run_4 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>]");
	source ();
	assert (builder.clusters.empty ());
	assert (!builder.errors->errors.empty ());
	auto e1 (builder.errors->errors [0]);
	assert (e1.second == lambda_p::context (1, 2, 1, 1, 3, 2));
}

void lambda_p_script_io_test::lambda::run_5 ()
{
	lambda_p_script_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>[]]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
}