#include "routine.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/container.h>
#include <lambda_p/core/pipe.h>
#include <lambda_p/core/scatter.h>
#include <lambda_p/core/gather.h>
#include <lambda_p/core/point.h>
#include <lambda_p/core/expression.h>

void lambda_p_test::routine::run ()
{
	run_1 ();
}

void lambda_p_test::routine::run_1 ()
{
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine);
	boost::shared_ptr <lambda_p::container> container (new lambda_p::container);
	routine->output->next = container;
	auto gather (boost::shared_ptr <lambda_p::core::gather> (new lambda_p::core::gather (routine->output, 2)));
	auto scatter (boost::shared_ptr <lambda_p::core::scatter> (new lambda_p::core::scatter (2)));
	routine->input = scatter;
	scatter->targets [0].push_back (boost::shared_ptr <lambda_p::core::point> (new lambda_p::core::point (gather, 0)));
	scatter->targets [1].push_back (boost::shared_ptr <lambda_p::core::point> (new lambda_p::core::point (gather, 1)));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> values;
	values.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	values.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	(*routine->input) (values);
	assert (container->results.size () == 2);
}