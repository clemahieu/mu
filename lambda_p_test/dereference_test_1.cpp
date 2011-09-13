#include "dereference_test_1.h"

#include <lambda_p/binder/dereference.h>
#include <lambda_p/binder/bound_routine.h>
#include <lambda_p/binder/null_binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/core/routine.h>

#include <sstream>

lambda_p_test::dereference_test_1::dereference_test_1(void)
{
}

lambda_p_test::dereference_test_1::~dereference_test_1(void)
{
}

void lambda_p_test::dereference_test_1::run ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::dereference> dereference (new ::lambda_p::binder::dereference);
    ::std::wstring name (L"null_binder");
    dereference->nodes [name] = null_binder;
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    ::lambda_p::core::statement * statement (routine->add_statement ());
    ::lambda_p::core::declaration * declaration (routine->add_declaration (0, 0));
    statement->add_argument (declaration);
    ::lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->add_argument (routine->add_reference (0, 0, 1, 0));
	::lambda_p::core::declaration * declaration2 (routine->add_declaration (1, 1));
	statement1->add_argument (declaration2);
	statement1->add_argument (routine->add_data (name, 1, 2));
    ::lambda_p::binder::routine_binder routine_binder;
    routine_binder.instances [declaration] = dereference;
	routine_binder (routine);
	assert (routine_binder.instances.find (declaration2) != routine_binder.instances.end ());
}