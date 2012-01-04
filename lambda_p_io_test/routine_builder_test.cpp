#include "routine_builder_test.h"

#include <lambda_p_io/builder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/entry.h>
#include <lambda_p/core/expression.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/container.h>
#include <lambda_p/core/pipe.h>
#include <lambda_p/core/identity.h>

void lambda_p_io_test::routine_builder_test::run ()
{	
	run_1 ();
	run_2 ();
}

void lambda_p_io_test::routine_builder_test::run_1 ()
{
	lambda_p_io::builder routine;
	routine (L"[~]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	(*(result->input)) (arguments);
	assert (routine.errors->errors.empty ());
	assert (container->results.empty ());
}

void lambda_p_io_test::routine_builder_test::run_2 ()
{
	lambda_p_io::builder routine;
	routine (L"[.identity]");
	assert (routine.routines.size () == 1);
	auto result (routine.routines [0]);
	auto container (boost::shared_ptr <lambda_p::container> (new lambda_p::container));
	result->output->next = container;
	std::vector <boost::shared_ptr <lambda_p::core::expression>> arguments;
	assert (result->input.get () != nullptr);
	(*(result->input)) (arguments);
	assert (routine.errors->errors.empty ());
	assert (container->results.empty ());
}