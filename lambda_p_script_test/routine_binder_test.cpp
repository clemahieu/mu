#include "routine_binder_test.h"

#include <lambda_p/binder/list.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/errors/error_list.h>

void lambda_p_test::routine_binder_test::run ()
{
	run_1 ();
}

void lambda_p_test::routine_binder_test::run_1 ()
{
	boost::shared_ptr <lambda_p::core::routine> inner_routine (new lambda_p::core::routine);
	boost::shared_ptr <lambda_p::binder::list> inner_nodes (new lambda_p::binder::list);
	lambda_p::errors::error_list problems;
	lambda_p_kernel::apply apply;
	lambda_p::binder::list declarations;
	apply.core (inner_routine, *inner_nodes, problems, declarations);
	assert (problems.errors.size () == 0);
}