#include "routine_binder_test.h"

#include <lambda_p_kernel/routine.h>
#include <lambda_p/binder/node_list.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p_kernel/bind_procedure.h>
#include <lambda_p_kernel/single_bind_routine.h>

void lambda_p_test::routine_binder_test::run ()
{
	run_1 ();
}

void lambda_p_test::routine_binder_test::run_1 ()
{
	boost::shared_ptr < lambda_p::core::routine> inner_routine (new lambda_p::core::routine);
	boost::shared_ptr < lambda_p_kernel::routine> rout (new lambda_p_kernel::routine (inner_routine));
	boost::shared_ptr < lambda_p::binder::node_list> inner_nodes (new lambda_p::binder::node_list);
	lambda_p_kernel::single_bind_routine single_bind_routine (rout, inner_nodes);
	lambda_p::errors::error_list problems;
	single_bind_routine (problems);
	assert (problems.errors.size () == 0);
}