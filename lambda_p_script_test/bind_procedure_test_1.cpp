#include "bind_procedure_test_1.h"

#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/core/routine.h>
#include <lambda_p_kernel/null_binder.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p_kernel/nodes/data.h>
#include <lambda_p/errors/error_list.h>

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
	lambda_p::binder::list nodes;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_2 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	lambda_p::binder::list nodes;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
    size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = declaration;
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (!problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_3 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = declaration;
	lambda_p::errors::error_list problems;
	lambda_p::binder::list nodes;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	nodes [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	bind_procedure (problems);
	assert (problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_4 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
    size_t declaration2 (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration2);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = declaration;
	statement->association->references.push_back (declaration2);
	lambda_p::binder::list nodes;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	nodes [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (!problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_5 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
	routine->surface->declarations.push_back (routine->add_declaration ());
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = declaration;
	statement->association->references.push_back (routine->inject_declaration (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::nodes::data (std::wstring (std::wstring ())))));
	lambda_p::binder::list nodes;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	nodes [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
}

void lambda_p_test::bind_procedure_test_1::run_6 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = declaration;
	lambda_p::binder::list nodes;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	nodes [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (nodes [statement->target].get () != nullptr);
}

// Tests to make sure dependent statement targets can be resolved by a previous statement's result
void lambda_p_test::bind_procedure_test_1::run_7 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = declaration;
	size_t declaration1 (routine->add_declaration ());
	statement->association->declarations.push_back (declaration1);
	lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->target = declaration1;
	lambda_p::binder::list nodes;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	nodes [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (nodes [statement->target].get () != nullptr);
}

// Tests to make sure binding works when a non-cyclic binding dependency exists that's not in written statement order i.e. out of order statements
void lambda_p_test::bind_procedure_test_1::run_8 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->declarations.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = declaration;
	lambda_p::core::statement * s2 (routine->add_statement ());
	s2->target = declaration;
	size_t d2 (routine->add_declaration ());
	s2->association->declarations.push_back (d2);
	size_t r (d2);
	statement->association->references.push_back (r);
	lambda_p::binder::list nodes;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	nodes [declaration] = boost::shared_ptr <lambda_p::binder::binder> (new lambda_p_kernel::null_binder);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (nodes [statement->target].get () != nullptr);
	assert (nodes [declaration].get () != nullptr);
	assert (nodes [r].get () != nullptr);
}