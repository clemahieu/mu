#include "builder.h"

#include <lambda_p/builder.h>
#include <lambda_p/core/routine.h>

#include <assert.h>

void lambda_p_test::builder::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::builder::run_1 ()
{
	lambda_p::builder builder;
	builder (L"\uffff");
	assert (builder.parser.error ().get () == nullptr);
	assert (builder.routines.routines->empty ());
}

void lambda_p_test::builder::run_2 ()
{
	lambda_p::builder builder;
	builder (L";[]\uffff");
	assert (builder.parser.error ().get () == nullptr);
	assert (builder.routines.routines->size () == 1);
}

void lambda_p_test::builder::run_3 ()
{
	lambda_p::builder builder;
	builder (L"a;[a]\uffff");
	assert (builder.parser.error ().get () == nullptr);
	assert (builder.routines.routines->size () == 1);
	auto routine (builder.routines.routines->operator[] (0));
}