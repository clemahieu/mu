#include "list_test.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/binder/list.h>

void lambda_p_test::list_test::run ()
{
	::lambda_p::core::routine routine;
	size_t group (routine.add_declaration ());
	routine.surface->results.push_back (group);
	::lambda_p::core::statement * statement (routine.add_statement (group));
	size_t result (routine.add_declaration ());
	statement->association->results.push_back (result);
	::boost::shared_ptr < ::lambda_p::binder::list_binder> binder (new ::lambda_p::binder::list_binder);
	routine.instances [group] = binder;
	::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > problems;
	binder->bind (statement, routine.instances, problems);
	assert (problems.empty ());
	assert (routine.instances [result].get () != NULL);
	assert (::boost::dynamic_pointer_cast < ::lambda_p::binder::list> (routine.instances [result]).get () != NULL);
	assert (::boost::dynamic_pointer_cast < ::lambda_p::binder::list> (routine.instances [result])->instances.size () == 0);

}