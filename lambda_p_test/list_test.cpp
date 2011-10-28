#include "list_test.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/null_binder.h>
#include <lambda_p_kernel/bind_procedure.h>

#include <boost/shared_ptr.hpp>

void lambda_p_test::list_test::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_test::list_test::run_1 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t group (routine->add_declaration ());
	routine->surface->results.push_back (group);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (group);
	size_t result (routine->add_declaration ());
	statement->association->results.push_back (result);
	boost::shared_ptr <lambda_p::binder::list_binder> binder (new lambda_p::binder::list_binder);
	lambda_p::errors::error_list problems;
	lambda_p::binder::node_list instances;
	instances [group] = binder;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (instances [result].get () != NULL);
	assert (boost::dynamic_pointer_cast <lambda_p::binder::list> (instances [result]).get () != NULL);
	assert (boost::dynamic_pointer_cast <lambda_p::binder::list> (instances [result])->instances.size () == 0);
}

void lambda_p_test::list_test::run_2 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t list (routine->add_declaration ());
	routine->surface->results.push_back (list);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (list);
	size_t result1 (routine->add_declaration ());
	size_t result2 (routine->add_declaration ());
	statement->association->results.push_back (result1);
	statement->association->results.push_back (result2);
	boost::shared_ptr <lambda_p::binder::list> binder (new lambda_p::binder::list);
	binder->instances.push_back (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::null_binder));
	binder->instances.push_back (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::null_binder));
	lambda_p::binder::node_list instances;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	instances [list] = binder;
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (instances [result1].get () != NULL);
	assert (instances [result2].get () != NULL);
}

void lambda_p_test::list_test::run_3 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t list (routine->add_declaration ());
	routine->surface->results.push_back (list);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target.push_back (list);
	size_t result1 (routine->add_declaration ());
	size_t result2 (routine->add_declaration ());
	statement->association->results.push_back (result1);
	statement->association->results.push_back (result2);
	boost::shared_ptr <lambda_p::binder::list> binder (new lambda_p::binder::list);
	binder->instances.push_back (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::null_binder));
	lambda_p::binder::node_list instances;
	instances [list] = binder;
	lambda_p_kernel::bind_procedure bind_procedure (routine, instances);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (!problems.errors.empty ());
}