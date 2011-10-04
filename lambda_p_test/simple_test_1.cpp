#include "simple_test_1.h"

#include <sstream>
#include <lambda_p/serialization/simple.h>
#include <iostream>

lambda_p_test::simple_test_1::simple_test_1(void)
{
}

lambda_p_test::simple_test_1::~simple_test_1(void)
{
}

void lambda_p_test::simple_test_1::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
	run_7 ();
	run_8 ();
}

void lambda_p_test::simple_test_1::run_1 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	::std::vector < ::lambda_p::errors::error *> problems;
    ::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (problems);
	assert (problems.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_2 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	signature->results.push_back (routine.add_declaration ());
	::std::vector < ::lambda_p::errors::error *> problems;
    ::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (problems);
	assert (problems.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_3 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	signature->results.push_back (routine.add_declaration ());
	signature->results.push_back (routine.add_declaration ());
	::std::vector < ::lambda_p::errors::error *> problems;
    ::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (problems);
	assert (problems.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_4 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::declaration * declaration (routine.add_declaration ());
	signature->results.push_back (declaration);
	signature->results.push_back (routine.add_declaration ());
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
	statement1->parameters.push_back (routine.add_reference (declaration));
	::std::vector < ::lambda_p::errors::error *> problems;
    ::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (problems);
	assert (problems.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_5 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    statement1->results.push_back (routine.add_declaration ());
	::std::vector < ::lambda_p::errors::error *> problems;
    ::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (problems);
	assert (problems.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_6 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    ::lambda_p::core::declaration * declaration (routine.add_declaration ());
    statement1->results.push_back (declaration);
	::std::vector < ::lambda_p::errors::error *> problems;
    ::lambda_p::core::statement * statement2 = routine.add_statement ();
    statement2->parameters.push_back (routine.add_reference (declaration));
    ::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (problems);
	assert (problems.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_7 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::declaration * declaration1 (routine.add_declaration ());
	signature->results.push_back (declaration1);
    ::lambda_p::core::declaration * declaration2 (routine.add_declaration ());
	signature->results.push_back (declaration2);
    ::lambda_p::core::declaration * declaration3 (routine.add_declaration ());
	signature->results.push_back (declaration3);
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    ::lambda_p::core::declaration * declaration4 (routine.add_declaration ());
    statement1->results.push_back (declaration4);
	statement1->parameters.push_back (routine.add_reference (declaration3));
	statement1->parameters.push_back (routine.add_reference (declaration2));
	::std::vector < ::lambda_p::errors::error *> problems;
    ::lambda_p::core::statement * statement2 = routine.add_statement ();
	statement2->parameters.push_back (routine.add_reference (declaration1));
    statement2->parameters.push_back (routine.add_reference (declaration4));
	statement2->parameters.push_back (routine.add_reference (declaration2));
    ::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (problems);
	assert (problems.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_8 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::declaration * declaration (routine.add_declaration ());
	signature->results.push_back (declaration);
	::lambda_p::core::statement * statement1 = routine.add_statement ();
	statement1->parameters.push_back (routine.add_reference (declaration));
	statement1->parameters.push_back (routine.add_data (::std::wstring ()));
	::std::vector < ::lambda_p::errors::error *> problems;
    ::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (problems);
	assert (problems.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}