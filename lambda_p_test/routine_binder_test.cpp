#include "routine_binder_test.h"

#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/binder/routine.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/bind_procedure.h>

void lambda_p_test::routine_binder_test::run ()
{
	run_1 ();
}

void lambda_p_test::routine_binder_test::run_1 ()
{
	::boost::shared_ptr < ::lambda_p::core::routine> outer_routine (new ::lambda_p::core::routine);
	size_t binder_parameter (outer_routine->add_declaration ());
	outer_routine->surface->results.push_back (binder_parameter);
	size_t routine_parameter (outer_routine->add_declaration ());
	outer_routine->surface->results.push_back (routine_parameter);
	size_t instances_parameter (outer_routine->add_declaration ());
	outer_routine->surface->results.push_back (instances_parameter);
	::lambda_p::core::statement * statement (outer_routine->add_statement (binder_parameter));
	statement->association->parameters.push_back (routine_parameter);
	statement->association->parameters.push_back (instances_parameter);
	::boost::shared_ptr < ::lambda_p::core::routine> inner_routine (new ::lambda_p::core::routine);
	::boost::shared_ptr < ::lambda_p::binder::routine_instances> instances (new ::lambda_p::binder::routine_instances);
	::boost::shared_ptr < ::lambda_p::binder::routine> rout (new ::lambda_p::binder::routine (inner_routine));
	::boost::shared_ptr < ::lambda_p::binder::routine_binder> binder (new ::lambda_p::binder::routine_binder);
	::lambda_p::binder::routine_instances bind_instances;
	bind_instances [0] = binder;
	bind_instances [1] = rout;
	bind_instances [2] = instances;
	::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > problems;
	binder->bind (statement, bind_instances, problems);
	assert (problems.size () == 0);
}