#include "builder.h"

#include <lambda_p_io/source.h>
#include <lambda_p_io/builder.h>
#include <lambda_p/routine.h>
#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p/expression.h>

#include <boost/bind.hpp>

void lambda_p_io_test::builder::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_io_test::builder::run_1 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	source ();
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
	auto routine (builder.routines [0]);
	assert (routine->body->dependencies.size () == 1);
	assert (routine->body->dependencies [0] == routine->parameters);
	assert (routine->parameters->dependencies.size () == 0);
	assert (routine->parameters->context == lambda_p::context (1, 1, 0, 1, 1, 0));
	assert (routine->body->context == lambda_p::context (1, 1, 0, 1, 4, 3));
}

void lambda_p_io_test::builder::run_2 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	source (L"[:~]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 2);
	auto routine1 (builder.routines [0]);
	auto routine2 (builder.routines [1]);
	assert (routine1->parameters->context == lambda_p::context (1, 1, 0, 1, 1, 0));
	assert (routine1->body->context == lambda_p::context (1, 1, 0, 1, 4, 3));
	assert (routine2->parameters->context == lambda_p::context (1, 5, 4, 1, 5, 4));
	assert (routine2->body->context == lambda_p::context (1, 5, 4, 1, 8, 7));
}

void lambda_p_io_test::builder::run_3 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; a b c] a [a b c] c]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
	auto routine (builder.routines [0]);
	assert (routine->body->context == lambda_p::context (1, 1, 0, 1, 25, 24));
	assert (routine->body->dependencies.size () == 3);
	auto d1 (boost::dynamic_pointer_cast <lambda_p::reference> (routine->body->dependencies [0]));
	assert (d1.get () != nullptr);
	auto d2 (boost::dynamic_pointer_cast <lambda_p::expression> (routine->body->dependencies [1]));
	assert (d2.get () != nullptr);
	assert (d2->context == lambda_p::context (1, 16, 15, 1, 22, 21));
	auto d3 (boost::dynamic_pointer_cast <lambda_p::reference> (routine->body->dependencies [2]));
	assert (d3.get () != nullptr);
	auto d11 (boost::dynamic_pointer_cast <lambda_p::expression> (d1->expression));
	assert (d11.get () != nullptr);
	assert (d11->context == lambda_p::context (1, 2, 1, 1, 12, 11));
	assert (d1->index == 0);
	assert (d11->dependencies.size () == 1);
	assert (d11->dependencies [0] == routine->parameters);
	assert (d2->dependencies.size () == 3);
	auto d21 (boost::dynamic_pointer_cast <lambda_p::reference> (d2->dependencies [0]));
	assert (d21.get () != nullptr);
	assert (d21->expression == d11);
	assert (d21->index == 0);
	auto d22 (boost::dynamic_pointer_cast <lambda_p::reference> (d2->dependencies [1]));
	assert (d22.get () != nullptr);
	assert (d22->expression == d11);
	assert (d22->index == 1);
	auto d23 (boost::dynamic_pointer_cast <lambda_p::reference> (d2->dependencies [2]));
	assert (d23.get () != nullptr);
	assert (d23->expression == d11);
	assert (d23->index == 2);
	assert (d3->expression == d11);
	assert (d3->index == 2);
}