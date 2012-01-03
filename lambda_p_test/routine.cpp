#include "routine.h"

#include <lambda_p/core/routine.h>
#include <lambda_p/container.h>
#include <lambda_p/core/pipe.h>
#include <lambda_p/core/scatter.h>
#include <lambda_p/core/gather.h>
#include <lambda_p/core/expression.h>
#include <lambda_p/core/connection.h>
#include <lambda_p/core/tee.h>
#include <lambda_p/core/entry.h>
#include <lambda_p/errors/error_list.h>

#include <boost/bind.hpp>

void lambda_p_test::routine::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_test::routine::run_1 ()
{
	lambda_p::errors::error_list errors;
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine (boost::bind (static_cast <void (lambda_p::errors::error_list::*) (boost::shared_ptr <lambda_p::errors::error>)>(&lambda_p::errors::error_list::operator()), &errors, _1)));
	boost::shared_ptr <lambda_p::container> container (new lambda_p::container);
	routine->output->next = container;
	auto gather (boost::shared_ptr <lambda_p::core::gather> (new lambda_p::core::gather (routine->output, 2)));
	auto scatter (boost::shared_ptr <lambda_p::core::scatter> (new lambda_p::core::scatter (routine->errors)));
	scatter->set_required (2);
	auto tee (boost::shared_ptr <lambda_p::core::tee> (new lambda_p::core::tee));
	tee->targets.push_back (scatter);
	auto entry (boost::shared_ptr <lambda_p::core::entry> (new lambda_p::core::entry));
	entry->next = tee;
	routine->input = entry;
	(*scatter) [0].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather, 0)));
	(*scatter) [1].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather, 1)));
	std::vector <boost::shared_ptr <lambda_p::core::expression>> values;
	values.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	values.push_back (boost::shared_ptr <lambda_p::core::expression> (new lambda_p::core::expression));
	(*routine->input) (values);
	assert (container->results.size () == 2);
}

void lambda_p_test::routine::run_2 ()
{
	lambda_p::errors::error_list errors;
	boost::shared_ptr <lambda_p::core::routine> routine (new lambda_p::core::routine (boost::bind (static_cast <void (lambda_p::errors::error_list::*) (boost::shared_ptr <lambda_p::errors::error>)>(&lambda_p::errors::error_list::operator()), &errors, _1)));
	boost::shared_ptr <lambda_p::container> container (new lambda_p::container);
	routine->output->next = container;
	auto gather1 (boost::shared_ptr <lambda_p::core::gather> (new lambda_p::core::gather (routine->output, 2)));
	auto gather2 (boost::shared_ptr <lambda_p::core::gather> (new lambda_p::core::gather (routine->output, 3)));
	auto scatter (boost::shared_ptr <lambda_p::core::scatter> (new lambda_p::core::scatter (routine->errors)));
	scatter->set_required (4);
	(*scatter) [0].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather2, 2)));
	(*scatter) [1].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather1, 1)));
	(*scatter) [2].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather1, 0)));
	(*scatter) [3].push_back (boost::shared_ptr <lambda_p::core::connection> (new lambda_p::core::connection (gather2, 0)));
	auto tee (boost::shared_ptr <lambda_p::core::tee> (new lambda_p::core::tee));
	tee->targets.push_back (scatter);
	auto entry (boost::shared_ptr <lambda_p::core::entry> (new lambda_p::core::entry));
	entry->next = tee;
	routine->input = entry;
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