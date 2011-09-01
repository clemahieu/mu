#include "simple_test_1.h"

#include <sstream>
#include <lambda_p/serialization/simple.h>

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
}

void lambda_p_test::simple_test_1::run_1 ()
{
	::lambda_p::core::routine routine (0);
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);	
}

void lambda_p_test::simple_test_1::run_2 ()
{
}

void lambda_p_test::simple_test_1::run_3 ()
{
}

void lambda_p_test::simple_test_1::run_4 ()
{
}

void lambda_p_test::simple_test_1::run_5 ()
{
}

void lambda_p_test::simple_test_1::run_6 ()
{
}