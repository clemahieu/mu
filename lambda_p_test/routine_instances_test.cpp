#include "routine_instances_test.h"

#include <lambda_p/binder/routine_instances.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p/binder/data.h>

void lambda_p_test::routine_instances_test::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
}

void lambda_p_test::routine_instances_test::run_1 ()
{
	lambda_p::binder::routine_instances one;
	lambda_p::binder::routine_instances two;
	lambda_p::errors::error_list problems;
	one.merge (two, problems);
	assert (problems.errors.empty ());
}

void lambda_p_test::routine_instances_test::run_2 ()
{
	lambda_p::binder::routine_instances one;
	lambda_p::binder::routine_instances two;
	lambda_p::errors::error_list problems;
	one [0] = boost::shared_ptr <lambda_p::binder::instance> (new lambda_p::binder::data (std::wstring ()));
	one.merge (two, problems);
	assert (problems.errors.empty ());
	assert (one.instances.size () == 1);
	assert (two.instances.empty ());
	assert (one [0].get () != nullptr);
}

void lambda_p_test::routine_instances_test::run_3 ()
{
	lambda_p::binder::routine_instances one;
	lambda_p::binder::routine_instances two;
	lambda_p::errors::error_list problems;
	two [0] = boost::shared_ptr <lambda_p::binder::instance> (new lambda_p::binder::data (std::wstring ()));
	one.merge (two, problems);
	assert (problems.errors.empty ());
	assert (one.instances.size () == 1);
	assert (two.instances.size () == 1);
	assert (one [0].get () != nullptr);
}

void lambda_p_test::routine_instances_test::run_4 ()
{
	lambda_p::binder::routine_instances one;
	lambda_p::binder::routine_instances two;
	lambda_p::errors::error_list problems;
	two [1] = boost::shared_ptr <lambda_p::binder::instance> (new lambda_p::binder::data (std::wstring ()));
	one.merge (two, problems);
	assert (problems.errors.empty ());
	assert (one.instances.size () == 2);
	assert (two.instances.size () == 2);
	assert (one [0].get () == nullptr);
	assert (one [1].get () != nullptr);
}

void lambda_p_test::routine_instances_test::run_5 ()
{
	lambda_p::binder::routine_instances one;
	lambda_p::binder::routine_instances two;
	lambda_p::errors::error_list problems;
	one [1] = boost::shared_ptr <lambda_p::binder::instance> (new lambda_p::binder::data (std::wstring ()));
	two [1] = boost::shared_ptr <lambda_p::binder::instance> (new lambda_p::binder::data (std::wstring ()));
	one.merge (two, problems);
	assert (!problems.errors.empty ());
}