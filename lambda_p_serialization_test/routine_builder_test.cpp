#include "routine_builder_test.h"

#include <lambda_p_serialization/builder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/entry.h>
#include <lambda_p/core/expression.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/container.h>
#include <lambda_p/core/pipe.h>
#include <lambda_p/core/identity.h>

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
}

void lambda_p_serialization_test::routine_builder_test::run_1 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	assert (result->input.get () != nullptr);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_serialization_test::routine_builder_test::run_2 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[] []");
	assert (routine.routines.size () == 2);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	assert (result->input.get () != nullptr);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_serialization_test::routine_builder_test::run_3 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[~]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	assert (result->input.get () != nullptr);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_serialization_test::routine_builder_test::run_4 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[~; a]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	auto e1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	arguments.push_back (e1);
	assert (result->input.get () != nullptr);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
	assert (container->results.size () == 1);
	assert (container->results [0] == e1);
}

void lambda_p_serialization_test::routine_builder_test::run_5 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[~; a]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	assert (result->input.get () != nullptr);
	(*(result->input)) (arguments);
	assert (!errors.errors.empty ());
}

void lambda_p_serialization_test::routine_builder_test::run_6 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[~; a b]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	auto a1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	auto a2 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	arguments.push_back (a1);
	arguments.push_back (a2);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_serialization_test::routine_builder_test::run_7 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[[~; a] a]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	auto a1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::identity));
	arguments.push_back (a1);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_serialization_test::routine_builder_test::run_8 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[[~; a b] a b]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	auto a1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::identity));
	auto a2 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	arguments.push_back (a1);
	arguments.push_back (a2);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_serialization_test::routine_builder_test::run_9 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[~; a; b]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	auto a1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	arguments.push_back (a1);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_serialization_test::routine_builder_test::run_10 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[[~; a b] a; c d]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	auto a1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::identity));
	auto a2 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	arguments.push_back (a1);
	arguments.push_back (a2);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
}

void lambda_p_serialization_test::routine_builder_test::run_11 ()
{
	lambda_p_serialization::builder routine;
	lambda_p::errors::error_list errors;
	routine (L"[[~; a b] a b; d; e]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	auto a1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::identity));
	auto a2 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	arguments.push_back (a1);
	arguments.push_back (a2);
	(*(result->input)) (arguments);
	assert (errors.errors.empty ());
}