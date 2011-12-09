#include "list_iterator.h"

#include <lambda_p/core/list.h>
#include <lambda_p/core/list_iterator.h>

#include <boost/shared_ptr.hpp>

void lambda_p_test::list_iterator::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
	run_5 ();
	run_6 ();
}

void lambda_p_test::list_iterator::run_1 ()
{
	boost::shared_ptr <lambda_p::core::list> list (new lambda_p::core::list);
	lambda_p::core::list_iterator current (list, false);
	lambda_p::core::list_iterator end (list, true);
	assert (current == end);
	assert (list->resolved ());
}

void lambda_p_test::list_iterator::run_2 ()
{
	boost::shared_ptr <lambda_p::core::list> list (new lambda_p::core::list);
	list->contents.push_back (boost::shared_ptr <lambda_p::core::expression> ());
	lambda_p::core::list_iterator current (list, false);
	lambda_p::core::list_iterator end (list, true);
	assert (current != end);
	assert ((*current).get () == nullptr);
	++current;
	assert (current == end);
	assert (!list->resolved ());
}

void lambda_p_test::list_iterator::run_3 ()
{
	boost::shared_ptr <lambda_p::core::list> list (new lambda_p::core::list);
	boost::shared_ptr <lambda_p::core::list> list2 (new lambda_p::core::list);
	list->contents.push_back (list2);
	lambda_p::core::list_iterator current (list, false);
	lambda_p::core::list_iterator end (list, true);
	assert (current == end);
	assert (list->resolved ());
}

void lambda_p_test::list_iterator::run_4 ()
{
	boost::shared_ptr <lambda_p::core::list> list (new lambda_p::core::list);
	boost::shared_ptr <lambda_p::core::list> list2 (new lambda_p::core::list);
	list2->contents.push_back (boost::shared_ptr <lambda_p::core::expression> ());
	list->contents.push_back (list2);
	lambda_p::core::list_iterator current (list, false);
	lambda_p::core::list_iterator end (list, true);
	assert (current != end);
	assert ((*current).get () == nullptr);
	assert (!list->resolved ());
}

void lambda_p_test::list_iterator::run_5 ()
{
	boost::shared_ptr <lambda_p::core::list> list (new lambda_p::core::list);
	boost::shared_ptr <lambda_p::core::expression> value (new lambda_p::core::expression);
	list->contents.push_back (value);
	lambda_p::core::list_iterator current (list, false);
	lambda_p::core::list_iterator end (list, true);
	assert (current != end);
	auto value2 (*current);
	assert (value2 == value);
	assert (list->resolved ());
}

void lambda_p_test::list_iterator::run_6 ()
{
	boost::shared_ptr <lambda_p::core::list> list (new lambda_p::core::list);
	boost::shared_ptr <lambda_p::core::list> list2 (new lambda_p::core::list);
	list->contents.push_back (list2);
	boost::shared_ptr <lambda_p::core::expression> value (new lambda_p::core::expression);
	list2->contents.push_back (value);
	lambda_p::core::list_iterator current (list, false);
	lambda_p::core::list_iterator end (list, true);
	assert (current != end);
	auto value2 (*current);
	assert (value2 == value);
	assert (list->resolved ());
}