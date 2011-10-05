#include "package_test_1.h"

#include <lambda_p/binder/package.h>
#include <lambda_p/binder/null_binder.h>
#include <lambda_p/core/statement.h>
#include <lambda_p/binder/routine_binder.h>
#include <lambda_p/core/routine.h>
#include <lambda_p/core/association.h>
#include <lambda_p/binder/data.h>

#include <sstream>

lambda_p_test::package_test_1::package_test_1(void)
{
}

lambda_p_test::package_test_1::~package_test_1(void)
{
}

void lambda_p_test::package_test_1::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_test::package_test_1::run_1 ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::package> package (new ::lambda_p::binder::package);
    ::std::wstring name (L"null_binder");
    package->nodes [name] = null_binder;
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
    ::lambda_p::core::statement * statement1 (routine->add_statement (declaration));
	size_t declaration2 (routine->add_declaration ());
	statement1->association->results.push_back (declaration2);
	statement1->association->parameters.push_back (routine->add_data (name));
    ::lambda_p::binder::routine_binder routine_binder (routine);
    routine_binder.instances [declaration] = package;
	routine_binder ();
	assert (!routine_binder.error ());
	assert (routine_binder.instances.find (declaration2) != routine_binder.instances.end ());
	assert (routine_binder.instances.find (declaration2)->second == null_binder);
}

void lambda_p_test::package_test_1::run_2 ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::package> inner (new ::lambda_p::binder::package);
    ::std::wstring name (L"null_binder");
    inner->nodes [name] = null_binder;
	::boost::shared_ptr < ::lambda_p::binder::package> outer (new ::lambda_p::binder::package);
	::std::wstring name2 (L"package");
	outer->nodes [name2] = inner;
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    size_t declaration (routine->add_declaration ());
    routine->surface->results.push_back (declaration);
    ::lambda_p::core::statement * statement1 (routine->add_statement (declaration));
	size_t declaration2 (routine->add_declaration ());
	statement1->association->results.push_back (declaration2);
	::std::wstring dname (L"package.null_binder");
	statement1->association->parameters.push_back (routine->add_data (dname));
    ::lambda_p::binder::routine_binder routine_binder (routine);
    routine_binder.instances [declaration] = outer;
	routine_binder ();
	assert (routine_binder.instances.find (declaration2) != routine_binder.instances.end ());
	assert (routine_binder.instances.find (declaration2)->second == null_binder);
}

void lambda_p_test::package_test_1::run_3 ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::package> package (new ::lambda_p::binder::package);
    ::std::wstring name (L"null_binder");
	::std::wstring junk (L"junk");
    package->nodes [name] = null_binder;
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
    ::lambda_p::core::statement * statement1 (routine->add_statement (declaration));
	statement1->association->parameters.push_back (declaration);
	size_t declaration2 (routine->add_declaration ());
	statement1->association->results.push_back (declaration2);
	statement1->association->parameters.push_back (routine->add_data (junk));
	statement1->association->parameters.push_back (routine->add_data (name));
    ::lambda_p::binder::routine_binder routine_binder (routine);
    routine_binder.instances [declaration] = package;
	routine_binder ();
	assert (routine_binder.error ());
}

void lambda_p_test::package_test_1::run_4 ()
{
    ::boost::shared_ptr < ::lambda_p::binder::null_binder> null_binder (new ::lambda_p::binder::null_binder);
    ::boost::shared_ptr < ::lambda_p::binder::package> package (new ::lambda_p::binder::package);
    ::std::wstring name (L"null_binder");
    package->nodes [name] = null_binder;
    ::boost::shared_ptr < ::lambda_p::core::routine> routine (new ::lambda_p::core::routine); 
    size_t declaration (routine->add_declaration ());
	routine->surface->results.push_back (declaration);
    ::lambda_p::core::statement * statement1 (routine->add_statement (declaration));
    size_t d1 (routine->add_declaration ());
	statement1->association->results.push_back (d1);
    size_t d2 (routine->add_declaration ());
	statement1->association->results.push_back (d2);
	statement1->association->parameters.push_back (routine->add_data (name));
    statement1->association->parameters.push_back (routine->add_data (name));
    ::lambda_p::binder::routine_binder routine_binder (routine);
    routine_binder.instances [declaration] = package;
	routine_binder ();
	assert (!routine_binder.error ());
	assert (routine_binder.instances.find (d1) != routine_binder.instances.end ());
	assert (routine_binder.instances.find (d2) != routine_binder.instances.end ());
}