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
}

void lambda_p_test::bind_procedure_test_1::run_1 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	lambda_p_kernel::bind_procedure bind_procedure (routine);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_2 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	lambda_p_kernel::bind_procedure bind_procedure (routine);
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
	lambda_p_kernel::bind_procedure bind_procedure (routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (declaration);
	bind_procedure.routine->instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
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
	lambda_p_kernel::bind_procedure bind_procedure (routine);
	bind_procedure.routine->instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
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
	lambda_p_kernel::bind_procedure bind_procedure (routine);
	bind_procedure.routine->instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
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
	lambda_p_kernel::bind_procedure bind_procedure (routine);
	bind_procedure.routine->instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (bind_procedure.routine->instances [statement->target [0]].get () != NULL);
}

void lambda_p_test::bind_procedure_test_1::run_7 ()
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
	lambda_p_kernel::bind_procedure bind_procedure (routine);
	bind_procedure.routine->instances [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (bind_procedure.routine->instances [statement->target [0]].get () != NULL);
	assert (bind_procedure.routine->instances [declaration].get () != NULL);
	assert (bind_procedure.routine->instances [r].get () != NULL);
}