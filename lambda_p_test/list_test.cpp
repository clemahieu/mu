#include "list_test.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/list_binder.h>
#include <lambda_p/binder/list.h>
#include <lambda_p/binder/null_binder.h>

void lambda_p_test::list_test::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_test::list_test::run_1 ()
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

void lambda_p_test::list_test::run_2 ()
{
	::lambda_p::core::routine routine;
	size_t list (routine.add_declaration ());
	routine.surface->results.push_back (list);
	::lambda_p::core::statement * statement (routine.add_statement (list));
	size_t result1 (routine.add_declaration ());
	size_t result2 (routine.add_declaration ());
	statement->association->results.push_back (result1);
	statement->association->results.push_back (result2);
	::boost::shared_ptr < ::lambda_p::binder::list> binder (new ::lambda_p::binder::list);
	binder->instances.push_back (::boost::shared_ptr < ::lambda_p::binder::instance> (new ::lambda_p::binder::null_binder));
	binder->instances.push_back (::boost::shared_ptr < ::lambda_p::binder::instance> (new ::lambda_p::binder::null_binder));
	routine.instances [list] = binder;
	::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > problems;
	binder->bind (statement, routine.instances, problems);
	assert (problems.empty ());
	assert (routine.instances [result1].get () != NULL);
	assert (routine.instances [result2].get () != NULL);
}

void lambda_p_test::list_test::run_3 ()
{
	::lambda_p::core::routine routine;
	size_t list (routine.add_declaration ());
	routine.surface->results.push_back (list);
	::lambda_p::core::statement * statement (routine.add_statement (list));
	size_t result1 (routine.add_declaration ());
	size_t result2 (routine.add_declaration ());
	statement->association->results.push_back (result1);
	statement->association->results.push_back (result2);
	::boost::shared_ptr < ::lambda_p::binder::list> binder (new ::lambda_p::binder::list);
	binder->instances.push_back (::boost::shared_ptr < ::lambda_p::binder::instance> (new ::lambda_p::binder::null_binder));
	routine.instances [list] = binder;
	::std::vector < ::boost::shared_ptr < ::lambda_p::errors::error> > problems;
	binder->bind (statement, routine.instances, problems);
	assert (!problems.empty ());
}