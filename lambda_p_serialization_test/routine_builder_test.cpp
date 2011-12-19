#include "routine_builder_test.h"

#include <lambda_p_serialization/builder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/entry.h>
#include <lambda_p/core/expression.h>

void lambda_p_serialization_test::routine_builder_test::run ()
{	
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
	run_9 ();
	run_10 ();
	run_11 ();
	run_12 ();
	run_13 ();
	run_14 ();
	run_15 ();
}

void lambda_p_serialization_test::routine_builder_test::run_1 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[] []");
	assert (routine.routines.routines->size () == 1);
	auto result (routine.routines.routines->operator[] (0));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	assert (result->input.get () != nullptr);
	(*(result->input)) (arguments);
}

void lambda_p_serialization_test::routine_builder_test::run_2 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a] []");
	assert (routine.routines.routines->size () == 1);
	auto result (routine.routines.routines->operator[] (0));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	auto a1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	assert (result->input.get () != nullptr);
	(*(result->input)) (arguments);
}

void lambda_p_serialization_test::routine_builder_test::run_3 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a b] []");
	assert (routine.routines.routines->size () == 1);
	auto result (routine.routines.routines->operator[] (0));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	auto a1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	assert (result->input.get () != nullptr);
	(*(result->input)) (arguments);
}

void lambda_p_serialization_test::routine_builder_test::run_4 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a] [a]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_5 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a b] [a b]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_6 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a; b] []");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_7 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a b] [a b; c d]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_8 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a b] [a b; c d; e]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_9 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a b] [a b;; e]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_10 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[] [[]]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_11 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a] [[a]]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_12 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a] [b [a; b]]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_13 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a] [[a]; b]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_14 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a] [[a] [a]; b c]");
	assert (routine.routines.routines->size () == 1);
}

void lambda_p_serialization_test::routine_builder_test::run_15 ()
{
	lambda_p_serialization::builder routine;
	routine (L"[a] [[a] [a];; b]");
	assert (routine.routines.routines->size () == 1);
}