#include "apply.h"

#include <lambda_p/apply.h>
#include <lambda_p/node.h>

#include <boost/make_shared.hpp>

void lambda_p_test::apply::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_test::apply::run_1 ()
{
	std::vector <boost::shared_ptr <lambda_p::node>> target;
	std::vector <boost::shared_ptr <lambda_p::node>> source;
	lambda_p::apply::merge (target, source);
	assert (target.size () == 0);
	assert (source.size () == 0);
}

void lambda_p_test::apply::run_2 ()
{
	std::vector <boost::shared_ptr <lambda_p::node>> target;
	target.push_back (boost::make_shared <lambda_p::node> ());
	std::vector <boost::shared_ptr <lambda_p::node>> source;
	lambda_p::apply::merge (target, source);
	assert (target.size () == 1);
	assert (source.size () == 0);
}

void lambda_p_test::apply::run_3 ()
{
	std::vector <boost::shared_ptr <lambda_p::node>> target;
	std::vector <boost::shared_ptr <lambda_p::node>> source;
	source.push_back (boost::make_shared <lambda_p::node> ());
	lambda_p::apply::merge (target, source);
	assert (target.size () == 1);
	assert (source.size () == 1);
	assert (target [0] == source [0]);
}

void lambda_p_test::apply::run_4 ()
{
	std::vector <boost::shared_ptr <lambda_p::node>> target;
	std::vector <boost::shared_ptr <lambda_p::node>> source;
	source.push_back (boost::shared_ptr <lambda_p::node> ());
	source.push_back (boost::make_shared <lambda_p::node> ());
	lambda_p::apply::merge (target, source);
	assert (target.size () == 2);
	assert (source.size () == 2);
	assert (target [0].get () == nullptr);
	assert (target [1] == source [1]);
}