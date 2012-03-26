#include <mu/script_test/topology/core.h>

#include <mu/core/errors/error_list.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/script/topology/core.h>
#include <mu/core/parameters.h>
#include <mu/script/topology/node.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

void mu::script_test::topology::core::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void mu::script_test::topology::core::run_1 ()
{
	auto routine (boost::make_shared <mu::core::routine> ());
	auto root (boost::make_shared <mu::core::expression> ());
	routine->body = root;
	auto parameters (boost::make_shared <mu::core::expression> ());
	root->dependencies.push_back (parameters);
	parameters->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	mu::script::topology::core order (routine->body);
	auto i (order.topology->expressions.begin ());
	assert (*i == parameters);
	++i;
	assert (*i == root);
	++i;
	assert (i == order.topology->expressions.end ());
	assert (order.acyclic);
}

void mu::script_test::topology::core::run_2 ()
{
	auto routine (boost::make_shared <mu::core::routine> ());
	auto root (boost::make_shared <mu::core::expression> ());
	routine->body = root;
	auto c1 (boost::make_shared <mu::core::expression> ());
	root->dependencies.push_back (c1);
	c1->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	auto c2 (boost::make_shared <mu::core::expression> ());
	root->dependencies.push_back (c2);
	c2->dependencies.push_back (c1);
	mu::script::topology::core order (routine->body);
	auto i (order.topology->expressions.begin ());
	assert (*i == c1);
	++i;
	assert (*i == c2);
	++i;
	assert (*i == root);
	++i;
	assert (i == order.topology->expressions.end ());
	assert (order.acyclic);
}

void mu::script_test::topology::core::run_3 ()
{
	auto routine (boost::make_shared <mu::core::routine> ());
	auto root (boost::make_shared <mu::core::expression> ());
	routine->body = root;
	auto parameters (boost::make_shared <mu::core::expression> ());
	parameters->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	auto r1 (boost::make_shared <mu::core::reference> (parameters, 0));
	root->dependencies.push_back (r1);
	mu::script::topology::core order (routine->body);
	auto i (order.topology->expressions.begin ());
	assert (*i == parameters);
	++i;
	assert (*i == root);
	++i;
	assert (i == order.topology->expressions.end ());
	assert (order.acyclic);
}

void mu::script_test::topology::core::run_4 ()
{
	auto routine (boost::make_shared <mu::core::routine> ());
	auto root (boost::make_shared <mu::core::expression> ());
	routine->body = root;
	auto expression1 (boost::make_shared <mu::core::expression> ());
	auto expression2 (boost::make_shared <mu::core::expression> ());
	expression1->dependencies.push_back (expression2);
	expression2->dependencies.push_back (expression1);
	root->dependencies.push_back (expression1);
	mu::script::topology::core core (routine->body);
	assert (!core.acyclic);
}