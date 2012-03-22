#include <mu/core_test/order.h>

#include <mu/core/errors/error_list.h>
#include <mu/core/routine.h>
#include <mu/core/expression.h>
#include <mu/core/reference.h>
#include <mu/core/order.h>
#include <mu/core/parameters.h>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

void mu::core_test::order::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
}

void mu::core_test::order::run_1 ()
{
	auto routine (boost::shared_ptr <mu::core::routine> (new mu::core::routine));
	auto root (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	routine->body = root;
	auto parameters (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	root->dependencies.push_back (parameters);
	parameters->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	mu::core::order order (routine->body);
	auto i (order.expressions.begin ());
	assert (*i == parameters);
	++i;
	assert (*i == root);
	++i;
	assert (i == order.expressions.end ());
}

void mu::core_test::order::run_2 ()
{
	auto routine (boost::shared_ptr <mu::core::routine> (new mu::core::routine));
	auto root (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	routine->body = root;
	auto c1 (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	root->dependencies.push_back (c1);
	c1->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	auto c2 (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	root->dependencies.push_back (c2);
	c2->dependencies.push_back (c1);
	mu::core::order order (routine->body);
	auto i (order.expressions.begin ());
	assert (*i == c1);
	++i;
	assert (*i == c2);
	++i;
	assert (*i == root);
	++i;
	assert (i == order.expressions.end ());
}

void mu::core_test::order::run_3 ()
{
	auto routine (boost::shared_ptr <mu::core::routine> (new mu::core::routine));
	auto root (boost::shared_ptr <mu::core::expression> (new mu::core::expression));
	routine->body = root;
	auto parameters (boost::make_shared <mu::core::expression> ());
	parameters->dependencies.push_back (boost::make_shared <mu::core::parameters> ());
	auto r1 (boost::shared_ptr <mu::core::reference> (new mu::core::reference (parameters, 0)));
	root->dependencies.push_back (r1);
	mu::core::order order (routine->body);
	auto i (order.expressions.begin ());
	assert (*i == parameters);
	++i;
	assert (*i == root);
	++i;
	assert (i == order.expressions.end ());
}