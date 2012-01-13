#include "visitor.h"

#include <lambda_p_test/test_visitor.h>
#include <lambda_p/expression.h>
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
	lambda_p::expression * expression (nullptr);
	lambda_p::node * node (nullptr);
	lambda_p::reference * reference (nullptr);
	(*visitor) (expression);	
	(*visitor) (node);	
	(*visitor) (reference);
	assert (visitor->expressions.size () == 1);
	assert (visitor->nodes.size () == 1);
	assert (visitor->references.size () == 1);
}

void lambda_p_test::visitor::run_2 ()
{
	boost::shared_ptr <lambda_p_test::test_visitor> vis (new lambda_p_test::test_visitor);	
	boost::shared_ptr <lambda_p::visitor> visitor (vis);
	lambda_p::expression * expression (nullptr);
	lambda_p::node * node (nullptr);
	lambda_p::reference * reference (nullptr);
	(*visitor) (expression);	
	(*visitor) (node);	
	(*visitor) (reference);
	assert (vis->expressions.size () == 1);
	assert (vis->nodes.size () == 1);
	assert (vis->references.size () == 1);
}

void lambda_p_test::visitor::run_3 ()
{
	boost::shared_ptr <lambda_p_test::test_visitor> vis (new lambda_p_test::test_visitor);	
	boost::shared_ptr <lambda_p::visitor> visitor (vis);
	lambda_p::expression * expression (new lambda_p::expression);
	lambda_p::node * node (new lambda_p::node);
	lambda_p::reference * reference (new lambda_p::reference (boost::shared_ptr <lambda_p::expression> (), 0));
	(*expression) (visitor.get ());	
	(*node) (visitor.get ());
	(*reference) (visitor.get ());
	assert (vis->expressions.size () == 1);
	assert (vis->nodes.size () == 1);
	assert (vis->references.size () == 1);
}