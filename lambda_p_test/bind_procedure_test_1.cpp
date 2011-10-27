#include "bind_procedure_test_1.h"

#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_kernel/null_binder.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/data.h>

#include <boost/shared_ptr.hpp>

lambda_p_test::bind_procedure_test_1::bind_procedure_test_1(void)
{
}

lambda_p_test::bind_procedure_test_1::~bind_procedure_test_1(void)
{
}

void lambda_p_test::bind_procedure_test_1::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
}

void lambda_p_test::bind_procedure_test_1::run_1 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	lambda_p::binder::routine_instances instances;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_2 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	lambda_p::binder::routine_instances instances;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
    size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (declaration);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (!problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_3 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (declaration);
	lambda_p::errors::error_list problems;
	lambda_p::binder::routine_instances instances;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	bind_procedure (problems);
	assert (problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_4 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
    size_t declaration2 (routine->add_declaration ());
	routine->surface->results.push_back (declaration2);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (declaration);
	statement->association->parameters.push_back (declaration2);
	lambda_p::binder::routine_instances instances;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (!problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_5 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
	routine->surface->results.push_back (routine->add_declaration ());
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (declaration);
	statement->association->parameters.push_back (routine->add_data (std::wstring ()));
	lambda_p::binder::routine_instances instances;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_6 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (declaration);
	lambda_p::binder::routine_instances instances;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (instances [statement->target [0]].get () != NULL);
}

// Tests to make sure dependent statement targets can be resolved by a previous statement's result
void lambda_p_test::bind_procedure_test_1::run_7 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (declaration);
	size_t declaration1 (routine->add_declaration ());
	statement->association->results.push_back (declaration1);
	lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->target.push_back (declaration1);
	lambda_p::binder::routine_instances instances;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (instances [statement->target [0]].get () != NULL);
}

// Tests to make sure binding works when a non-cyclic binding dependency exists that's not in written statement order i.e. out of order statements
void lambda_p_test::bind_procedure_test_1::run_8 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (declaration);
	lambda_p::core::statement * s2 (routine->add_statement ());
	s2->target.push_back (declaration);
	size_t d2 (routine->add_declaration ());
	s2->association->results.push_back (d2);
	size_t r (d2);
	statement->association->parameters.push_back (r);
	lambda_p::binder::routine_instances instances;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (instances [statement->target [0]].get () != NULL);
	assert (instances [declaration].get () != NULL);
	assert (instances [r].get () != NULL);
}