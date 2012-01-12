#include "builder.h"

#include <lambda_p_io/source.h>
#include <lambda_p_io/builder.h>
#include <lambda_p/routine.h>
#include <lambda_p/call.h>
#include <lambda_p/reference.h>
#include <lambda_p/parameters.h>

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
}

void lambda_p_io_test::builder::run_2 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[:~]");
	source (L"[:~]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 2);
}

void lambda_p_io_test::builder::run_3 ()
{
	lambda_p_io::builder builder;
	lambda_p_io::source source (boost::bind (&lambda_p_io::lexer::lexer::operator(), &builder.lexer, _1));
	source (L"[[:~; a b c d] a b [b c d] d]");
	assert (builder.errors->errors.empty ());
	assert (builder.routines.size () == 1);
	auto routine (builder.routines [0]);
	assert (routine->call->dependencies.size () == 5);
	auto d11 (boost::dynamic_pointer_cast <lambda_p::call> (routine->call->dependencies [0]));
	assert (d11.get () != nullptr);
	auto d12 (boost::dynamic_pointer_cast <lambda_p::reference> (routine->call->dependencies [1]));
	assert (d12.get () != nullptr);
	auto d13 (boost::dynamic_pointer_cast <lambda_p::reference> (routine->call->dependencies [2]));
	assert (d13.get () != nullptr);
	auto d14 (boost::dynamic_pointer_cast <lambda_p::call> (routine->call->dependencies [3]));
	assert (d14.get () != nullptr);
	auto d15 (boost::dynamic_pointer_cast <lambda_p::reference> (routine->call->dependencies [4]));
	assert (d15.get () != nullptr);
	assert (d11->dependencies.size () == 1);
	assert (d11->dependencies [0] == routine->parameters);
	assert (d12->expression == d11);
	assert (d12->index == 0);
	assert (d13->expression == d11);
	assert (d13->index == 1);
	assert (d14->dependencies.size () == 3);
	auto d141 (boost::dynamic_pointer_cast <lambda_p::reference> (d14->dependencies [0]));
	assert (d141.get () != nullptr);
	auto d142 (boost::dynamic_pointer_cast <lambda_p::reference> (d14->dependencies [1]));
	assert (d142.get () != nullptr);
	auto d143 (boost::dynamic_pointer_cast <lambda_p::reference> (d14->dependencies [2]));
	assert (d143.get () != nullptr);
	assert (d141->expression == d11);
	assert (d141->index == 1);
	assert (d142->expression == d11);
	assert (d142->index == 2);
	assert (d143->expression == d11);
	assert (d143->index == 3);
	assert (d15->expression == d11);
	assert (d15->index == 3);
}