#include "visitor.h"

#include <lambda_p_test/test_visitor.h>
#include <lambda_p/call.h>
#include <lambda_p/node.h>
#include <lambda_p/reference.h>

#include <boost/shared_ptr.hpp>

void lambda_p_test::visitor::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_test::visitor::run_1 ()
{
	boost::shared_ptr <lambda_p_test::test_visitor> visitor (new lambda_p_test::test_visitor);
	lambda_p::call * call (nullptr);
	lambda_p::node * node (nullptr);
	lambda_p::reference * reference (nullptr);
	(*visitor) (call);	
	(*visitor) (node);	
	(*visitor) (reference);
	assert (visitor->calls.size () == 1);
	assert (visitor->nodes.size () == 1);
	assert (visitor->references.size () == 1);
}

void lambda_p_test::visitor::run_2 ()
{
	boost::shared_ptr <lambda_p_test::test_visitor> vis (new lambda_p_test::test_visitor);	
	boost::shared_ptr <lambda_p::visitor> visitor (vis);
	lambda_p::call * call (nullptr);
	lambda_p::node * node (nullptr);
	lambda_p::reference * reference (nullptr);
	(*visitor) (call);	
	(*visitor) (node);	
	(*visitor) (reference);
	assert (vis->calls.size () == 1);
	assert (vis->nodes.size () == 1);
	assert (vis->references.size () == 1);
}

void lambda_p_test::visitor::run_3 ()
{
	boost::shared_ptr <lambda_p_test::test_visitor> vis (new lambda_p_test::test_visitor);	
	boost::shared_ptr <lambda_p::visitor> visitor (vis);
	lambda_p::call * call (new lambda_p::call);
	lambda_p::node * node (new lambda_p::node);
	lambda_p::reference * reference (new lambda_p::reference (boost::shared_ptr <lambda_p::set> (), 0));
	(*call) (visitor.get ());	
	(*node) (visitor.get ());
	(*reference) (visitor.get ());
	assert (vis->calls.size () == 1);
	assert (vis->nodes.size () == 1);
	assert (vis->references.size () == 1);
}