#include "routine.h"

#include <lambda_p/routine.h>
#include <lambda_p/container.h>
#include <lambda_p/pipe.h>
#include <lambda_p/scatter.h>
#include <lambda_p/gather.h>
#include <lambda_p/node.h>
#include <lambda_p/connection.h>
#include <lambda_p/tee.h>
#include <lambda_p/entry.h>
#include <lambda_p/errors/error_list.h>

#include <boost/bind.hpp>

void lambda_p_test::routine::run ()
{
	//run_1 ();
	//run_2 ();
}

void lambda_p_test::routine::run_1 ()
{
	auto errors (boost::shared_ptr <lambda_p::errors::error_target> (new lambda_p::errors::error_list));
	boost::shared_ptr <lambda_p::routine> routine (new lambda_p::routine (errors));
	boost::shared_ptr <lambda_p::container> container (new lambda_p::container);
	routine->output->next = container;
	auto gather (boost::shared_ptr <lambda_p::gather> (new lambda_p::gather (routine->output)));
	auto scatter (boost::shared_ptr <lambda_p::scatter> (new lambda_p::scatter (2, routine->errors)));
	auto tee (boost::shared_ptr <lambda_p::tee> (new lambda_p::tee));
	tee->targets.push_back (scatter);
	auto entry (boost::shared_ptr <lambda_p::entry> (new lambda_p::entry (errors)));
	entry->next = tee;
	routine->input = entry;
	(*scatter) [0].push_back ((*gather) (gather));
	(*scatter) [1].push_back ((*gather) (gather));
	std::vector <boost::shared_ptr <lambda_p::node>> values;
	values.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	values.push_back (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	(*routine->input) (values);
	assert (container->results.size () == 2);
}

void lambda_p_test::routine::run_2 ()
{
	//auto errors (boost::shared_ptr <lambda_p::errors::error_target> (new lambda_p::errors::error_list));
	//boost::shared_ptr <lambda_p::routine> routine (new lambda_p::routine (errors));
	//boost::shared_ptr <lambda_p::container> container (new lambda_p::container);
	//routine->output->next = container;
	//auto gather1 (boost::shared_ptr <lambda_p::gather> (new lambda_p::gather (routine->output, 2)));
	//(*scatter) [2].push_back (boost::shared_ptr <lambda_p::connection> (new lambda_p::connection (gather1, 0)));
	//(*scatter) [1].push_back (boost::shared_ptr <lambda_p::connection> (new lambda_p::connection (gather1, 1)));
	//auto gather2 (boost::shared_ptr <lambda_p::gather> (new lambda_p::gather (routine->output, 3)));
	//auto scatter (boost::shared_ptr <lambda_p::scatter> (new lambda_p::scatter (4, routine->errors)));
	//gather1->target = boost::shared_ptr <lambda_p::connection> (new lambda_p::connection (gather2, 1));
	//(*scatter) [0].push_back (boost::shared_ptr <lambda_p::connection> (new lambda_p::connection (gather2, 2)));
	//(*scatter) [3].push_back (boost::shared_ptr <lambda_p::connection> (new lambda_p::connection (gather2, 0)));
	//auto tee (boost::shared_ptr <lambda_p::tee> (new lambda_p::tee));
	//tee->targets.push_back (scatter);
	//auto entry (boost::shared_ptr <lambda_p::entry> (new lambda_p::entry (errors)));
	//entry->next = tee;
	//routine->input = entry;
	//auto v1 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	//auto v2 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	//auto v3 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	//auto v4 (boost::shared_ptr <lambda_p::node> (new lambda_p::node));
	//std::vector <boost::shared_ptr <lambda_p::node>> values;
	//values.push_back (v1);
	//values.push_back (v2);
	//values.push_back (v3);
	//values.push_back (v4);
	//(*routine->input) (values);
	//assert (container->results.size () == 4);
	//assert (container->results [0].get () == v4.get ());
	//assert (container->results [1].get () == v3.get ());
	//assert (container->results [2].get () == v2.get ());
	//assert (container->results [3].get () == v1.get ());
}