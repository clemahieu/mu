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
	signature->add_argument (routine->add_declaration (0, 0));
	::lambda_p::core::statement * statement (routine->add_statement ());
	statement->add_argument (routine->add_reference (0, 0, 1, 0));
	routine_binder (routine);
	assert (routine_binder.error ());
}

void lambda_p_test::routine_binder_test_1::run_3 ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	::lambda_p::core::statement * signature (routine->add_statement ());
	::lambda_p::core::node * declaration (routine->add_declaration (0, 0));
	signature->add_argument (declaration);
	::lambda_p::core::statement * statement (routine->add_statement ());
	statement->add_argument (routine->add_reference (0, 0, 1, 0));
	routine_binder.instances [declaration] = ::boost::shared_ptr < ::lambda_p::binder::node_binder> (new ::lambda_p::binder::null_binder);
	routine_binder (routine);
	assert (!routine_binder.error ());
}

void lambda_p_test::routine_binder_test_1::run_4 ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	::lambda_p::core::statement * signature (routine->add_statement ());
	::lambda_p::core::node * declaration (routine->add_declaration (0, 0));
	signature->add_argument (declaration);
	signature->add_argument (routine->add_declaration (0, 1));
	::lambda_p::core::statement * statement (routine->add_statement ());
	statement->add_argument (routine->add_reference (0, 0, 1, 0));
	statement->add_argument (routine->add_reference (0, 1, 1, 1));
	routine_binder.instances [declaration] = ::boost::shared_ptr < ::lambda_p::binder::node_binder> (new ::lambda_p::binder::null_binder);
	routine_binder (routine);
	assert (routine_binder.error ());
}

void lambda_p_test::routine_binder_test_1::run_5 ()
{
	::lambda_p::binder::routine_binder routine_binder;
	::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine);
	::lambda_p::core::statement * signature (routine->add_statement ());
	::lambda_p::core::node * declaration (routine->add_declaration (0, 0));
	signature->add_argument (declaration);
	signature->add_argument (routine->add_declaration (0, 1));
	::lambda_p::core::statement * statement (routine->add_statement ());
	statement->add_argument (routine->add_reference (0, 0, 1, 0));
	statement->add_argument (routine->add_data (::std::wstring (), 1, 1));
	routine_binder.instances [declaration] = ::boost::shared_ptr < ::lambda_p::binder::node_binder> (new ::lambda_p::binder::null_binder);
	routine_binder (routine);
	assert (!routine_binder.error ());
}