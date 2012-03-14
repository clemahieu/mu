#include "visitor.h"

#include <mu/core_test/test_visitor.h>
#include <mu/core/expression.h>
#include <mu/core/node.h>
#include <mu/core/reference.h>
#include <mu/core/routine.h>
#include <mu/core/parameters.h>

#include <boost/shared_ptr.hpp>

void mu::core_test::visitor::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::core_test::visitor::run_1 ()
{
	boost::shared_ptr <mu::core_test::test_visitor> visitor (new mu::core_test::test_visitor);
	mu::core::expression * expression (nullptr);
	mu::core::parameters * parameters (nullptr);
	mu::core::node * node (nullptr);
	mu::core::reference * reference (nullptr);
	mu::core::routine * routine (nullptr);
	(*visitor) (expression);	
	(*visitor) (parameters);
	(*visitor) (node);	
	(*visitor) (reference);
	(*visitor) (routine);
	assert (visitor->expressions.size () == 1);
	assert (visitor->parameters.size () == 1);
	assert (visitor->nodes.size () == 1);
	assert (visitor->references.size () == 1);
	assert (visitor->routines.size () == 1);
}

void mu::core_test::visitor::run_2 ()
{
	boost::shared_ptr <mu::core_test::test_visitor> vis (new mu::core_test::test_visitor);	
	boost::shared_ptr <mu::core::visitor> visitor (vis);
	mu::core::expression * expression (nullptr);
	mu::core::parameters * parameters (nullptr);
	mu::core::node * node (nullptr);
	mu::core::reference * reference (nullptr);
	mu::core::routine * routine (nullptr);
	(*visitor) (expression);	
	(*visitor) (parameters);
	(*visitor) (node);	
	(*visitor) (reference);
	(*visitor) (routine);
	assert (vis->expressions.size () == 1);
	assert (vis->parameters.size () == 1);
	assert (vis->nodes.size () == 1);
	assert (vis->references.size () == 1);
	assert (vis->routines.size () == 1);
}

void mu::core_test::visitor::run_3 ()
{
	boost::shared_ptr <mu::core_test::test_visitor> vis (new mu::core_test::test_visitor);	
	boost::shared_ptr <mu::core::visitor> visitor (vis);
	mu::core::expression * expression (new mu::core::expression);
	mu::core::parameters * parameters (new mu::core::parameters);
	mu::core::node * node (new mu::core::node);
	mu::core::reference * reference (new mu::core::reference (boost::shared_ptr <mu::core::expression> (), 0));
	mu::core::routine * routine (new mu::core::routine);
	(*expression) (visitor.get ());	
	(*parameters) (visitor.get ());
	(*node) (visitor.get ());
	(*reference) (visitor.get ());
	(*routine) (visitor.get ());
	assert (vis->expressions.size () == 1);
	assert (vis->parameters.size () == 1);
	assert (vis->nodes.size () == 1);
	assert (vis->references.size () == 1);
	assert (vis->routines.size () == 1);
}