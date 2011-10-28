#include "single_bind_routine.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/core/statement.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p_kernel/routine.h>

lambda_p_kernel::single_bind_routine::single_bind_routine (boost::shared_ptr <lambda_p_kernel::routine> inner_routine_a, boost::shared_ptr <lambda_p::binder::node_list> inner_nodes_a)
	: binder_m (new lambda_p_kernel::apply),
	outer_routine (new lambda_p::core::routine),
	outer_nodes (new lambda_p::binder::node_list)
{
	size_t binder_parameter (outer_routine->add_declaration ());
	outer_routine->surface->results.push_back (binder_parameter);
	size_t routine_parameter (outer_routine->add_declaration ());
	outer_routine->surface->results.push_back (routine_parameter);
	size_t nodes_parameter (outer_routine->add_declaration ());
	outer_routine->surface->results.push_back (nodes_parameter);
	statement = outer_routine->add_statement ();
	statement->target = binder_parameter;
	statement->association->parameters.push_back (routine_parameter);
	statement->association->parameters.push_back (nodes_parameter);
	(*outer_nodes) [0] = binder_m;
	(*outer_nodes) [1] = inner_routine_a;
	(*outer_nodes) [2] = inner_nodes_a;
}


void lambda_p_kernel::single_bind_routine::operator () (lambda_p::errors::error_list & problems)
{
	binder_m->bind (statement, *outer_nodes, problems);
}