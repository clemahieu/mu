#include "unbindable_statement_test.h"

#include <lambda_p/binder/data.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/routine_instances.h>
#include <lambda_p_kernel/single_bind_routine.h>
#include <lambda_p_kernel/routine.h>

#include <boost/shared_ptr.hpp>

void lambda_p_test::unbindable_statement_test::run ()
{
	boost::shared_ptr < lambda_p::binder::data> data (new lambda_p::binder::data (std::wstring ()));
	boost::shared_ptr < lambda_p::core::routine> routine (new lambda_p::core::routine);
	size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
	lambda_p::core::statement * statement (routine->add_statement (declaration));
	boost::shared_ptr < lambda_p::binder::routine_instances> instances (new lambda_p::binder::routine_instances);
	(*instances) [declaration] = data;
	boost::shared_ptr < lambda_p_kernel::routine> target (new lambda_p_kernel::routine (routine));
	lambda_p_kernel::single_bind_routine bind_action (target, instances);
	std::vector < boost::shared_ptr < lambda_p::errors::error> > problems;
	bind_action (problems);
	assert (problems.size () == 1);
}