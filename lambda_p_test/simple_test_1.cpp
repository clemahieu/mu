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
	::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (target);
    ::std::wstring str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_2 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	signature->add_argument (routine.add_declaration ());
	::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (target);
    ::std::wstring str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_3 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	signature->add_argument (routine.add_declaration ());
	signature->add_argument (routine.add_declaration ());
	::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (target);
    ::std::wstring str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_4 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::declaration * declaration (routine.add_declaration ());
	signature->add_argument (declaration);
	signature->add_argument (routine.add_declaration ());
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
	statement1->add_argument (routine.add_reference (declaration));
	::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (target);
    ::std::wstring str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_5 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    statement1->add_argument (routine.add_declaration ());
	::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (target);
    ::std::wstring str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_6 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    ::lambda_p::core::declaration * declaration (routine.add_declaration ());
    statement1->add_argument (declaration);
	::std::wstringstream target;
    ::lambda_p::core::statement * statement2 = routine.add_statement ();
    statement2->add_argument (routine.add_reference (declaration));
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (target);
    ::std::wstring str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_7 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::declaration * declaration1 (routine.add_declaration ());
	signature->add_argument (declaration1);
    ::lambda_p::core::declaration * declaration2 (routine.add_declaration ());
	signature->add_argument (declaration2);
    ::lambda_p::core::declaration * declaration3 (routine.add_declaration ());
	signature->add_argument (declaration3);
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    ::lambda_p::core::declaration * declaration4 (routine.add_declaration ());
    statement1->add_argument (declaration4);
	statement1->add_argument (routine.add_reference (declaration3));
	statement1->add_argument (routine.add_reference (declaration2));
	::std::wstringstream target;
    ::lambda_p::core::statement * statement2 = routine.add_statement ();
	statement2->add_argument (routine.add_reference (declaration1));
    statement2->add_argument (routine.add_reference (declaration4));
	statement2->add_argument (routine.add_reference (declaration2));
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (target);
    ::std::wstring str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}

void lambda_p_test::simple_test_1::run_8 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::declaration * declaration (routine.add_declaration ());
	signature->add_argument (declaration);
	::lambda_p::core::statement * statement1 = routine.add_statement ();
	statement1->add_argument (routine.add_reference (declaration));
	statement1->add_argument (routine.add_data (::std::wstring ()));
	::std::wstringstream target;
	::lambda_p::serialization::simple < ::std::wstringstream> serializer (target);
	routine.validate (target);
    ::std::wstring str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::wstring str (target.str ());
}