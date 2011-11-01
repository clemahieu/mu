#include "list_test.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/null_binder.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p/errors/error_list.h>

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
	routine->surface->declarations.push_back (group);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = group;
	size_t result (routine->add_declaration ());
	statement->association->declarations.push_back (result);
	boost::shared_ptr <lambda_p::binder::list_binder> binder (new lambda_p::binder::list_binder);
	lambda_p::errors::error_list problems;
	lambda_p::binder::node_list nodes;
	nodes [group] = binder;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (nodes [result].get () != nullptr);
	assert (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [result]).get () != nullptr);
	assert (boost::dynamic_pointer_cast <lambda_p::binder::list> (nodes [result])->nodes.size () == 0);
}

void lambda_p_test::list_test::run_2 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t list (routine->add_declaration ());
	routine->surface->declarations.push_back (list);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = list;
	size_t result1 (routine->add_declaration ());
	size_t result2 (routine->add_declaration ());
	statement->association->declarations.push_back (result1);
	statement->association->declarations.push_back (result2);
	boost::shared_ptr <lambda_p::binder::list> binder (new lambda_p::binder::list);
	binder->nodes.push_back (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::null_binder));
	binder->nodes.push_back (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::null_binder));
	lambda_p::binder::node_list nodes;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	nodes [list] = binder;
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (problems.errors.empty ());
	assert (nodes [result1].get () != nullptr);
	assert (nodes [result2].get () != nullptr);
}

void lambda_p_test::list_test::run_3 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t list (routine->add_declaration ());
	routine->surface->declarations.push_back (list);
	lambda_p::core::statement * statement (routine->add_statement ());
	statement->target = list;
	size_t result1 (routine->add_declaration ());
	size_t result2 (routine->add_declaration ());
	statement->association->declarations.push_back (result1);
	statement->association->declarations.push_back (result2);
	boost::shared_ptr <lambda_p::binder::list> binder (new lambda_p::binder::list);
	binder->nodes.push_back (boost::shared_ptr <lambda_p::binder::node> (new lambda_p_kernel::null_binder));
	lambda_p::binder::node_list nodes;
	nodes [list] = binder;
	lambda_p_kernel::bind_procedure bind_procedure (routine, nodes);
	lambda_p::errors::error_list problems;
	bind_procedure (problems);
	assert (!problems.errors.empty ());
}