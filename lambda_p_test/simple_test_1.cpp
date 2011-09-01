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
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);	
	assert (target.str () == "");
}

void lambda_p_test::simple_test_1::run_2 ()
{
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);	
	::lambda_p::core::routine routine;
	serializer.routine (&routine);
	::std::string str (target.str ());
	assert (true);
}

void lambda_p_test::simple_test_1::run_3 ()
{
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);	
	::lambda_p::core::routine routine;
	routine.identifiers.push_back (::lambda_p::core::identifier ());
	routine.parameters.push_back (&(routine.identifiers [0]));
	serializer.routine (&routine);
	::std::string str (target.str ());
	assert (true);
}

void lambda_p_test::simple_test_1::run_4 ()
{
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);	
	::lambda_p::core::routine routine;
	routine.identifiers.push_back (::lambda_p::core::identifier ());
	routine.identifiers.push_back (::lambda_p::core::identifier ());
	routine.parameters.push_back (&(routine.identifiers [0]));
	routine.parameters.push_back (&(routine.identifiers [1]));
	serializer.routine (&routine);
	::std::string str (target.str ());
	assert (true);
}

void lambda_p_test::simple_test_1::run_5 ()
{
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);	
	::lambda_p::core::routine routine;
	routine.identifiers.push_back (::lambda_p::core::identifier ());
	routine.identifiers.push_back (::lambda_p::core::identifier ());
	routine.body.push_back (::lambda_p::core::statement (&routine.identifiers [0], &routine.identifiers [1]));
	serializer.routine (&routine);
	::std::string str (target.str ());
	assert (true);
}

void lambda_p_test::simple_test_1::run_6 ()
{
	::std::stringstream target;
	::lambda_p::serialization::simple < ::std::stringstream> serializer (target);	
	::lambda_p::core::routine routine;
	routine.identifiers.push_back (::lambda_p::core::identifier ());
	routine.identifiers.push_back (::lambda_p::core::identifier ());
	routine.body.push_back (::lambda_p::core::statement (&routine.identifiers [0], &routine.identifiers [1]));
	::lambda_p::core::data data;
	routine.body [0].arguments.push_back (&data);
	serializer.routine (&routine);
	::std::string str (target.str ());
	assert (true);
}