#include "lambda.h"

#include <lambda_p_io/builder.h>
#include <lambda_p_io/source.h>
#include <lambda_p/routine.h>
#include <lambda_p/cluster.h>
#include <lambda_p/expression.h>

#include <boost/bind.hpp>

void lambda_p_io_test::lambda::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_io_test::lambda::run_1 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>[]]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	assert (routine->body->dependencies.size () == 1);
	auto lambda (boost::dynamic_pointer_cast <lambda_p::routine> (routine->body->dependencies [0]));
	assert (lambda.get () != nullptr);
}

void lambda_p_io_test::lambda::run_2 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=> thing]");
	source ();
	assert (builder.clusters.empty ());
	assert (!builder.errors->errors.empty ());
	auto e1 (builder.errors->errors [0]);
	assert (e1.second == lambda_p::context (1, 2, 1, 1, 9, 8));
}

void lambda_p_io_test::lambda::run_3 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[=>]");
	source ();
	assert (builder.clusters.empty ());
	assert (!builder.errors->errors.empty ());
	auto e1 (builder.errors->errors [0]);
	assert (e1.second == lambda_p::context (1, 2, 1, 1, 3, 2));
}