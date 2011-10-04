#include "structure_test_1.h"

#include <lambda_p/binder/structure.h>
#include <lambda_p/binder/null_binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/core/routine.h>

#include <sstream>

lambda_p_test::structure_test_1::structure_test_1(void)
{
}

lambda_p_test::structure_test_1::~structure_test_1(void)
{
}

void lambda_p_test::structure_test_1::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_test::structure_test_1::run_1 ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::structure> dereference (new ::lambda_p::binder::structure);
    ::std::wstring name (L"null_binder");
    dereference->nodes [name] = null_binder;
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    ::lambda_p::core::statement * statement (routine->add_statement ());
    ::lambda_p::core::declaration * declaration (routine->add_declaration ());
	statement->results.push_back (declaration);
    ::lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->parameters.push_back (routine->add_reference (declaration));
	::lambda_p::core::declaration * declaration2 (routine->add_declaration ());
	statement1->results.push_back (declaration2);
	statement1->parameters.push_back (routine->add_data (name));
    ::lambda_p::binder::routine_binder routine_binder;
    routine_binder.instances [declaration] = dereference;
	routine_binder (routine);
	assert (routine_binder.instances.find (declaration2) != routine_binder.instances.end ());
	assert (routine_binder.instances.find (declaration2)->second == null_binder);
}

void lambda_p_test::structure_test_1::run_2 ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::structure> dereference (new ::lambda_p::binder::structure);
    ::std::wstring name (L"null_binder");
    dereference->nodes [name] = null_binder;
	::boost::shared_ptr < ::lambda_p::binder::structure> dereference2 (new ::lambda_p::binder::structure);
	::std::wstring name2 (L"dereference");
	dereference2->nodes [name2] = dereference;
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    ::lambda_p::core::statement * statement (routine->add_statement ());
    ::lambda_p::core::declaration * declaration (routine->add_declaration ());
    statement->results.push_back (declaration);
    ::lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->parameters.push_back (routine->add_reference (declaration));
	::lambda_p::core::declaration * declaration2 (routine->add_declaration ());
	statement1->results.push_back (declaration2);
	statement1->parameters.push_back (routine->add_data (name2));
	statement1->parameters.push_back (routine->add_data (name));
    ::lambda_p::binder::routine_binder routine_binder;
    routine_binder.instances [declaration] = dereference2;
	routine_binder (routine);
	assert (routine_binder.instances.find (declaration2) != routine_binder.instances.end ());
	assert (routine_binder.instances.find (declaration2)->second == null_binder);
}

void lambda_p_test::structure_test_1::run_3 ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::structure> dereference (new ::lambda_p::binder::structure);
    ::std::wstring name (L"null_binder");
	::std::wstring junk (L"junk");
    dereference->nodes [name] = null_binder;
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    ::lambda_p::core::statement * statement (routine->add_statement ());
    ::lambda_p::core::declaration * declaration (routine->add_declaration ());
    statement->results.push_back (declaration);
    ::lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->parameters.push_back (routine->add_reference (declaration));
	::lambda_p::core::declaration * declaration2 (routine->add_declaration ());
	statement1->results.push_back (declaration2);
	statement1->parameters.push_back (routine->add_data (junk));
	statement1->parameters.push_back (routine->add_data (name));
    ::lambda_p::binder::routine_binder routine_binder;
    routine_binder.instances [declaration] = dereference;
	routine_binder (routine);
	assert (routine_binder.error ());
}

void lambda_p_test::structure_test_1::run_4 ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::structure> dereference (new ::lambda_p::binder::structure);
    ::std::wstring name (L"null_binder");
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    ::lambda_p::core::statement * statement (routine->add_statement ());
    ::lambda_p::core::declaration * declaration (routine->add_declaration ());
    statement->results.push_back (declaration);
    ::lambda_p::core::declaration * declaration2 (routine->add_declaration ());
    statement->results.push_back (declaration2);
    ::lambda_p::core::statement * statement1 (routine->add_statement ());
	statement1->parameters.push_back (routine->add_reference (declaration));
	statement1->parameters.push_back (routine->add_reference (declaration2));
	statement1->parameters.push_back (routine->add_data (name));
    ::lambda_p::binder::routine_binder routine_binder;
    routine_binder.instances [declaration] = dereference;
	routine_binder.instances [declaration2] = null_binder;
	routine_binder (routine);
	assert (!routine_binder.error ());
	assert (dereference->nodes.find (name) != dereference->nodes.end ());
	assert (dereference->nodes [name] == null_binder);
}