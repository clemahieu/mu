#include "order.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p/routine.h>
#include <lambda_p/expression.h>
#include <lambda_p/reference.h>
#include <lambda_p/order.h>

#include <boost/shared_ptr.hpp>

void lambda_p_test::order::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void lambda_p_test::order::run_1 ()
{
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine (lambda_p::context ())));
	auto root (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context ())));
	routine->body = root;
	auto parameters (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context ())));
	root->dependencies.push_back (parameters);
	parameters->dependencies.push_back (routine->parameters);
	lambda_p::order order (routine->body, routine->parameters);
	auto i (order.expressions.begin ());
	assert (*i == parameters);
	++i;
	assert (*i == root);
	++i;
	assert (i == order.expressions.end ());
}

void lambda_p_test::order::run_2 ()
{
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine (lambda_p::context ())));
	auto root (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context ())));
	routine->body = root;
	auto c1 (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context ())));
	root->dependencies.push_back (c1);
	c1->dependencies.push_back (routine->parameters);
	auto c2 (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context ())));
	root->dependencies.push_back (c2);
	c2->dependencies.push_back (c1);
	lambda_p::order order (routine->body, routine->parameters);
	auto i (order.expressions.begin ());
	assert (*i == c1);
	++i;
	assert (*i == c2);
	++i;
	assert (*i == root);
	++i;
	assert (i == order.expressions.end ());
}

void lambda_p_test::order::run_3 ()
{
	auto routine (boost::shared_ptr <lambda_p::routine> (new lambda_p::routine (lambda_p::context ())));
	auto root (boost::shared_ptr <lambda_p::expression> (new lambda_p::expression (lambda_p::context ())));
	routine->body = root;
	auto r1 (boost::shared_ptr <lambda_p::reference> (new lambda_p::reference (routine->parameters, 0)));
	root->dependencies.push_back (r1);
	lambda_p::order order (routine->body, routine->parameters);
	auto i (order.expressions.begin ());
	assert (*i == root);
	++i;
	assert (i == order.expressions.end ());
}