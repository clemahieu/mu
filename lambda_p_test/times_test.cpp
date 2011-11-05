#include "times_test.h"

#include <lambda_p/builder.h>
#include <lambda_p/binder/list.h>
#include <lambda_p_kernel/identity.h>
#include <lambda_p_kernel/times.h>
#include <lambda_p_kernel/routine.h>
#include <lambda_p_kernel/number.h>
#include <lambda_p_kernel/apply.h>
#include <lambda_p/errors/error_list.h>

void lambda_p_test::times_test::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_test::times_test::run_1 ()
{
	lambda_p::builder loop_routine;
	loop_routine (L"res; identity; identity identity; res; :;");
	boost::shared_ptr <lambda_p::binder::list> loop_nodes (new lambda_p::binder::list);
	loop_nodes->operator[] (0) = boost::shared_ptr <lambda_p_kernel::identity> (new lambda_p_kernel::identity);
	lambda_p::builder test_routine;
	test_routine (L"result; times routine nodes count; times routine nodes count; result; :;");
	lambda_p::binder::list test_nodes;
	test_nodes [0] = boost::shared_ptr <lambda_p_kernel::times> (new lambda_p_kernel::times);	;
	test_nodes [1] = boost::shared_ptr <lambda_p_kernel::routine> (new lambda_p_kernel::routine (loop_routine.routines.routines->operator[] (0)));
	test_nodes [2] = loop_nodes;
	test_nodes [3] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (0));
	lambda_p_kernel::apply apply;
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (test_routine.routines.routines->operator[] (0)));
	lambda_p::errors::error_list problems;
	lambda_p::binder::list declarations;
	apply.core (*routine, test_nodes, problems, declarations);
	assert (declarations.nodes.size () == 1);
	boost::shared_ptr <lambda_p::binder::list> nodes (boost::dynamic_pointer_cast <lambda_p::binder::list> (declarations [0]));
	assert (nodes.get () != nullptr);
	assert (nodes->nodes.size () == 1);
	boost::shared_ptr <lambda_p_kernel::identity> identity (boost::dynamic_pointer_cast <lambda_p_kernel::identity> (nodes->operator[] (0)));
	assert (identity.get () != nullptr);
}

void lambda_p_test::times_test::run_2 ()
{
	lambda_p::builder loop_routine;
	loop_routine (L"res; identity; identity identity; res; :;");
	boost::shared_ptr <lambda_p::binder::list> loop_nodes (new lambda_p::binder::list);
	loop_nodes->operator[] (0) = boost::shared_ptr <lambda_p_kernel::identity> (new lambda_p_kernel::identity);
	lambda_p::builder test_routine;
	test_routine (L"result; times routine nodes count; times routine nodes count; result; :;");
	lambda_p::binder::list test_nodes;
	test_nodes [0] = boost::shared_ptr <lambda_p_kernel::times> (new lambda_p_kernel::times);	;
	test_nodes [1] = boost::shared_ptr <lambda_p_kernel::routine> (new lambda_p_kernel::routine (loop_routine.routines.routines->operator[] (0)));
	test_nodes [2] = loop_nodes;
	test_nodes [3] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (1));
	lambda_p_kernel::apply apply;
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (test_routine.routines.routines->operator[] (0)));
	lambda_p::errors::error_list problems;
	lambda_p::binder::list declarations;
	apply.core (*routine, test_nodes, problems, declarations);
	assert (declarations.nodes.size () == 1);
	boost::shared_ptr <lambda_p::binder::list> nodes (boost::dynamic_pointer_cast <lambda_p::binder::list> (declarations [0]));
	assert (nodes.get () != nullptr);
	assert (nodes->nodes.size () == 1);
	boost::shared_ptr <lambda_p_kernel::identity> identity (boost::dynamic_pointer_cast <lambda_p_kernel::identity> (nodes->operator[] (0)));
	assert (identity.get () != nullptr);
}

void lambda_p_test::times_test::run_3 ()
{
	lambda_p::builder loop_routine;
	loop_routine (L"res; identity; identity identity; res; :;");
	boost::shared_ptr <lambda_p::binder::list> loop_nodes (new lambda_p::binder::list);
	loop_nodes->operator[] (0) = boost::shared_ptr <lambda_p_kernel::identity> (new lambda_p_kernel::identity);
	lambda_p::builder test_routine;
	test_routine (L"result; times routine nodes count; times routine nodes count; result; :;");
	lambda_p::binder::list test_nodes;
	test_nodes [0] = boost::shared_ptr <lambda_p_kernel::times> (new lambda_p_kernel::times);	;
	test_nodes [1] = boost::shared_ptr <lambda_p_kernel::routine> (new lambda_p_kernel::routine (loop_routine.routines.routines->operator[] (0)));
	test_nodes [2] = loop_nodes;
	test_nodes [3] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (5));
	lambda_p_kernel::apply apply;
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (test_routine.routines.routines->operator[] (0)));
	lambda_p::errors::error_list problems;
	lambda_p::binder::list declarations;
	apply.core (*routine, test_nodes, problems, declarations);
	assert (declarations.nodes.size () == 1);
	boost::shared_ptr <lambda_p::binder::list> nodes (boost::dynamic_pointer_cast <lambda_p::binder::list> (declarations [0]));
	assert (nodes.get () != nullptr);
	assert (nodes->nodes.size () == 1);
	boost::shared_ptr <lambda_p_kernel::identity> identity (boost::dynamic_pointer_cast <lambda_p_kernel::identity> (nodes->operator[] (0)));
	assert (identity.get () != nullptr);
}

void lambda_p_test::times_test::run_4 ()
{
	lambda_p::builder loop_routine;
	loop_routine (L"; identity; identity identity; res; :;");
	boost::shared_ptr <lambda_p::binder::list> loop_nodes (new lambda_p::binder::list);
	loop_nodes->operator[] (0) = boost::shared_ptr <lambda_p_kernel::identity> (new lambda_p_kernel::identity);
	lambda_p::builder test_routine;
	test_routine (L"result; times routine nodes count; times routine nodes count; result; :;");
	lambda_p::binder::list test_nodes;
	test_nodes [0] = boost::shared_ptr <lambda_p_kernel::times> (new lambda_p_kernel::times);	;
	test_nodes [1] = boost::shared_ptr <lambda_p_kernel::routine> (new lambda_p_kernel::routine (loop_routine.routines.routines->operator[] (0)));
	test_nodes [2] = loop_nodes;
	test_nodes [3] = boost::shared_ptr <lambda_p_kernel::number> (new lambda_p_kernel::number (1));
	lambda_p_kernel::apply apply;
	boost::shared_ptr <lambda_p_kernel::routine> routine (new lambda_p_kernel::routine (test_routine.routines.routines->operator[] (0)));
	lambda_p::errors::error_list problems;
	lambda_p::binder::list declarations;
	apply.core (*routine, test_nodes, problems, declarations);
	assert (!problems.errors.empty ());
}