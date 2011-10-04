#include "routine_binder_test_1.h"

#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/binder/null_binder.h>

#include <boost/shared_ptr.hpp>

lambda_p_test::routine_binder_test_1::routine_binder_test_1(void)
{
}

lambda_p_test::routine_binder_test_1::~routine_binder_test_1(void)
{
}

void lambda_p_test::routine_binder_test_1::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
}

void lambda_p_test::routine_binder_test_1::run_1 ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	routine->add_statement ();
	routine_binder (routine);
	assert (!routine_binder.error ());
}

void lambda_p_test::routine_binder_test_1::run_2 ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	::lambda_p::core::statement * signature (routine->add_statement ());
    ::lambda_p::core::declaration * declaration (routine->add_declaration ());
	signature->results.push_back (declaration);
	::lambda_p::core::statement * statement (routine->add_statement ());
	statement->parameters.push_back (routine->add_reference (declaration));
	routine_binder (routine);
	assert (routine_binder.error ());
}

void lambda_p_test::routine_binder_test_1::run_3 ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	::lambda_p::core::statement * signature (routine->add_statement ());
	::lambda_p::core::declaration * declaration (routine->add_declaration ());
	signature->results.push_back (declaration);
	::lambda_p::core::statement * statement (routine->add_statement ());
	statement->parameters.push_back (routine->add_reference (declaration));
	routine_binder.instances [declaration] = ::boost::shared_ptr < ::lambda_p::binder::node_binder> (new ::lambda_p::binder::null_binder);
	routine_binder (routine);
	assert (!routine_binder.error ());
}

void lambda_p_test::routine_binder_test_1::run_4 ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	::lambda_p::core::statement * signature (routine->add_statement ());
	::lambda_p::core::declaration * declaration (routine->add_declaration ());
	signature->results.push_back (declaration);
    ::lambda_p::core::declaration * declaration2 (routine->add_declaration ());
	signature->results.push_back (declaration2);
	::lambda_p::core::statement * statement (routine->add_statement ());
	statement->parameters.push_back (routine->add_reference (declaration));
	statement->parameters.push_back (routine->add_reference (declaration2));
	routine_binder.instances [declaration] = ::boost::shared_ptr < ::lambda_p::binder::node_binder> (new ::lambda_p::binder::null_binder);
	routine_binder (routine);
	assert (routine_binder.error ());
}

void lambda_p_test::routine_binder_test_1::run_5 ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	::lambda_p::core::statement * signature (routine->add_statement ());
	::lambda_p::core::declaration * declaration (routine->add_declaration ());
	signature->results.push_back (declaration);
	signature->results.push_back (routine->add_declaration ());
	::lambda_p::core::statement * statement (routine->add_statement ());
	statement->parameters.push_back (routine->add_reference (declaration));
	statement->parameters.push_back (routine->add_data (::std::wstring ()));
	routine_binder.instances [declaration] = ::boost::shared_ptr < ::lambda_p::binder::node_binder> (new ::lambda_p::binder::null_binder);
	routine_binder (routine);
	assert (!routine_binder.error ());
}

void lambda_p_test::routine_binder_test_1::run_6 ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	::lambda_p::core::statement * signature (routine->add_statement ());
	::lambda_p::core::declaration * declaration (routine->add_declaration ());
	signature->results.push_back (declaration);
	::lambda_p::core::statement * statement (routine->add_statement ());
	::lambda_p::core::reference * reference (routine->add_reference (declaration));
	statement->parameters.push_back (reference);
	routine_binder.instances [declaration] = ::boost::shared_ptr < ::lambda_p::binder::node_binder> (new ::lambda_p::binder::null_binder);
	routine_binder (routine);
	assert (!routine_binder.error ());
	assert (routine_binder.instances.find (reference) != routine_binder.instances.end ());
}