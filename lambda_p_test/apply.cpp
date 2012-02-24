#include "apply.h"

#include <core/apply.h>
#include <core/node.h>
#include <core/segment.h>

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
	std::vector <boost::shared_ptr <mu::core::node>> target;
	std::vector <boost::shared_ptr <mu::core::node>> source;
	mu::core::apply::merge (target, source);
	assert (target.size () == 0);
	assert (source.size () == 0);
}

void lambda_p_test::apply::run_2 ()
{
	std::vector <boost::shared_ptr <mu::core::node>> target;
	target.push_back (boost::make_shared <mu::core::node> ());
	std::vector <boost::shared_ptr <mu::core::node>> source;
	mu::core::apply::merge (target, source);
	assert (target.size () == 1);
	assert (source.size () == 0);
}

void lambda_p_test::apply::run_3 ()
{
	std::vector <boost::shared_ptr <mu::core::node>> target;
	std::vector <boost::shared_ptr <mu::core::node>> source;
	source.push_back (boost::make_shared <mu::core::node> ());
	mu::core::apply::merge (target, source);
	assert (target.size () == 1);
	assert (source.size () == 1);
	assert (target [0] == source [0]);
}

void lambda_p_test::apply::run_4 ()
{
	std::vector <boost::shared_ptr <mu::core::node>> target;
	std::vector <boost::shared_ptr <mu::core::node>> source;
	source.push_back (boost::shared_ptr <mu::core::node> ());
	source.push_back (boost::make_shared <mu::core::node> ());
	mu::core::apply::merge (target, source);
	assert (target.size () == 2);
	assert (source.size () == 2);
	assert (target [0].get () == nullptr);
	assert (target [1] == source [1]);
}