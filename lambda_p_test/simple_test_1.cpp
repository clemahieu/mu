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
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	signature->add_argument (routine.add_result (0, 0));
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
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	signature->add_argument (routine.add_result (0, 0));
	signature->add_argument (routine.add_result (0, 1));
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
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	signature->add_argument (routine.add_result (0, 0));
	signature->add_argument (routine.add_result (0, 1));
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
	statement1->add_argument (routine.add_result_ref (0, 0, 1, 0));
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
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    statement1->add_argument (routine.add_result (1, 0));
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
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    statement1->add_argument (routine.add_result (1, 0));
	::std::stringstream target;
    ::lambda_p::core::statement * statement2 = routine.add_statement ();
    statement2->add_argument (routine.add_result_ref (1, 0, 2, 0));
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}

void lambda_p_test::simple_test_1::run_7 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	signature->add_argument (routine.add_result (0, 0));
	signature->add_argument (routine.add_result (0, 1));
	signature->add_argument (routine.add_result (0, 2));
    ::lambda_p::core::statement * statement1 = routine.add_statement ();
    statement1->add_argument (routine.add_result (1, 0));
	statement1->add_argument (routine.add_result_ref (0, 2, 1, 1));
	statement1->add_argument (routine.add_result_ref (0, 1, 1, 2));
	::std::stringstream target;
    ::lambda_p::core::statement * statement2 = routine.add_statement ();
	statement2->add_argument (routine.add_result_ref (0, 0, 2, 0));
    statement2->add_argument (routine.add_result_ref (1, 0, 2, 1));
	statement2->add_argument (routine.add_result_ref (0, 1, 2, 2));
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}

void lambda_p_test::simple_test_1::run_8 ()
{
	::lambda_p::core::routine routine;
	::lambda_p::core::statement * signature = routine.add_statement ();
	signature->add_argument (routine.add_result (0, 0));
	::lambda_p::core::statement * statement1 = routine.add_statement ();
	statement1->add_argument (routine.add_result_ref (0, 0, 1, 0));
	statement1->add_argument (routine.add_data (::boost::shared_array <uint8_t> (new uint8_t [0]), 0, 1, 1));
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);
	routine.validate (target);
    ::std::string str1 (target.str ());
	assert (str1.size () == 0);
	serializer.routine (&routine);
    ::std::string str (target.str ());
}