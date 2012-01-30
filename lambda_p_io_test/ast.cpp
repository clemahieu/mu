#include "ast.h"

#include <lambda_p/expression.h>
#include <lambda_p/routine.h>
#include <lambda_p_io/builder.h>
#include <lambda_p_io/ast/expression.h>
#include <lambda_p_io/ast/identifier.h>
#include <lambda_p_io/ast/cluster.h>

#include <boost/bind.hpp>

void lambda_p_io_test::ast::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_io_test::ast::run_1 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[.ast []]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	assert (routine->body->dependencies.size () == 1);
	auto cl (boost::dynamic_pointer_cast <lambda_p_io::ast::cluster> (routine->body->dependencies [0]));
	assert (cl.get () != nullptr);
	assert (cl->expressions.size () == 0);
}

void lambda_p_io_test::ast::run_2 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[.ast thing]");
	source ();
	assert (!builder.errors->errors.empty ());
	assert (builder.clusters.empty ());
}

void lambda_p_io_test::ast::run_3 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[.ast [[]]]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.clusters.size () == 1);
	auto cluster (builder.clusters [0]);
	assert (cluster->routines.size () == 1);
	auto routine (cluster->routines [0]);
	assert (routine->body->dependencies.size () == 1);
	auto cl (boost::dynamic_pointer_cast <lambda_p_io::ast::cluster> (routine->body->dependencies [0]));
	assert (cl.get () != nullptr);
	assert (cl->expressions.size () == 1);
	auto expression (cl->expressions [0]);
}