#include "test_visitor.h"

void lambda_p_test::test_visitor::operator () (lambda_p::set * set_a)
{
	sets.push_back (set_a);
}

void lambda_p_test::test_visitor::operator () (lambda_p::call * call_a)
{
	calls.push_back (call_a);
}

void lambda_p_test::test_visitor::operator () (lambda_p::reference * reference_a)
{
	references.push_back (reference_a);
}

void lambda_p_test::test_visitor::operator () (lambda_p::node * node_a)
{
	nodes.push_back (node_a);
}
