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
}

void lambda_p_test::simple_test_1::run_1 ()
{
	::lambda_p::core::routine routine (0);
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}

void lambda_p_test::simple_test_1::run_2 ()
{
	::lambda_p::core::routine routine (1);
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}

void lambda_p_test::simple_test_1::run_3 ()
{
	::lambda_p::core::routine routine (2);
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}

void lambda_p_test::simple_test_1::run_4 ()
{
	::lambda_p::core::routine routine (2);
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    statement1->add_argument (routine.add_parameter_ref (0, 0, 0));
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}

void lambda_p_test::simple_test_1::run_5 ()
{
	::lambda_p::core::routine routine (0);
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    statement1->add_argument (routine.add_result (0, 0));
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}

void lambda_p_test::simple_test_1::run_6 ()
{
	::lambda_p::core::routine routine (0);
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    statement1->add_argument (routine.add_result (0, 0));
	::std::stringstream target;
    ::lambda_p::core::statement * statement2 = routine.add_statement ();
    statement2->add_argument (routine.add_result_ref (0, 0, 1, 0));
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}

void lambda_p_test::simple_test_1::run_7 ()
{
	::lambda_p::core::routine routine (3);
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    statement1->add_argument (routine.add_result (0, 0));
	statement1->add_argument (routine.add_parameter_ref (2, 0, 1));
	statement1->add_argument (routine.add_parameter_ref (1, 0, 2));
	::std::stringstream target;
    ::lambda_p::core::statement * statement2 = routine.add_statement ();
	statement2->add_argument (routine.add_parameter_ref (0, 1, 0));
    statement2->add_argument (routine.add_result_ref (0, 0, 1, 1));
	statement2->add_argument (routine.add_parameter_ref (1, 1, 2));
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}