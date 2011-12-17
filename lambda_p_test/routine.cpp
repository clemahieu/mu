#include "routine.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/container.h>
#include <lambda_p/core/pipe.h>
#include <lambda_p/core/scatter.h>
#include <lambda_p/core/gather.h>
#include <lambda_p/core/expression.h>
#include <lambda_p/core/connection.h>
#include <lambda_p/core/tee.h>

void lambda_p_test::routine::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::routine::run_1 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	boost::shared_ptr <lambda_p::container> container (new lambda_p::container);
	routine->output->next = container;
	auto gather (boost::shared_ptr <lambda_p::core::gather> (new lambda_p::core::gather (routine->output, 2)));
	auto scatter (boost::shared_ptr <lambda_p::core::scatter> (new lambda_p::core::scatter (2)));
	auto tee (boost::shared_ptr <lambda_p::core::tee> (new lambda_p::core::tee));
	tee->targets.push_back (scatter);
	routine->input = tee;
	scatter->targets [0].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather, 0)));
	scatter->targets [1].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather, 1)));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> values;
	values.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	values.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	(*routine->input) (values);
	assert (container->results.size () == 2);
}

void lambda_p_test::routine::run_2 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	boost::shared_ptr <lambda_p::container> container (new lambda_p::container);
	routine->output->next = container;
	auto gather1 (boost::shared_ptr <lambda_p::core::gather> (new lambda_p::core::gather (routine->output, 2)));
	auto gather2 (boost::shared_ptr <lambda_p::core::gather> (new lambda_p::core::gather (routine->output, 3)));
	auto scatter (boost::shared_ptr <lambda_p::core::scatter> (new lambda_p::core::scatter (4)));
	scatter->targets [0].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather2, 2)));
	scatter->targets [1].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather1, 1)));
	scatter->targets [2].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather1, 0)));
	scatter->targets [3].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather2, 0)));
	auto tee (boost::shared_ptr <lambda_p::core::tee> (new lambda_p::core::tee));
	tee->targets.push_back (scatter);
	routine->input = tee;
	gather1->target = boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather2, 1));
	auto v1 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	auto v2 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	auto v3 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	auto v4 (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> values;
	values.push_back (v1);
	values.push_back (v2);
	values.push_back (v3);
	values.push_back (v4);
	(*routine->input) (values);
	assert (container->results.size () == 4);
	assert (container->results [0].get () == v4.get ());
	assert (container->results [1].get () == v3.get ());
	assert (container->results [2].get () == v2.get ());
	assert (container->results [3].get () == v1.get ());
}