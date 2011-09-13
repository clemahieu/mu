#include "dereference_binder_test.h"

#include <lambda_p/binder/dereference_binder.h>
#include <lambda_p/binder/dereference.h>
#include <lambda_p/binder/bound_routine.h>
#include <lambda_p/binder/null_binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/core/routine.h>

#include <sstream>

lambda_p_test::dereference_binder_test::dereference_binder_test(void)
{
}

lambda_p_test::dereference_binder_test::~dereference_binder_test(void)
{
}

void lambda_p_test::dereference_binder_test::run ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::dereference> dereference (new ::lambda_p::binder::dereference);
    ::std::wstring name (L"null_binder");
    dereference->nodes [name] = null_binder;
    ::lambda_p::binder::dereference_binder binder;
    ::lambda_p::binder::routine_binder routine_binder;
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    ::lambda_p::core::statement * statement (routine->add_statement ());
    ::lambda_p::core::declaration * declaration (routine->add_declaration (0, 0));
    statement->add_argument (declaration);
    routine_binder.instances [declaration] = dereference;
    ::lambda_p::core::statement * statement1 (routine->add_statement ());
    ::lambda_p::core::reference * reference (routine->add_reference (0, 0, 1, 0));
}