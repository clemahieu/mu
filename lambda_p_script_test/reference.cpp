#include "reference.h"

#include <lambda_p_script/reference.h>
#include <lambda_p/node.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/context.h>
#include <lambda_p_script/cluster/node.h>

#include <boost/make_shared.hpp>

void lambda_p_script_test::reference::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_script_test::reference::run_1 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	boost::shared_ptr <lambda_p::node> node (new lambda_p::node);
	lambda_p_script::reference reference (0, 0);
	lambda_p_script::context context (boost::make_shared <lambda_p_script::cluster::node> (), boost::make_shared <lambda_p::node> (), 1);
	context.nodes [0].push_back (node);
	std::vector <boost::shared_ptr <lambda_p::node>> target;
	reference (errors, context, target);
	assert (errors->errors.empty ());
	assert (target.size () == 1);
	assert (target [0] == node);
}

void lambda_p_script_test::reference::run_2 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	boost::shared_ptr <lambda_p::node> node1 (new lambda_p::node);
	boost::shared_ptr <lambda_p::node> node2 (new lambda_p::node);
	lambda_p_script::reference reference (0, 1);
	lambda_p_script::context context (boost::make_shared <lambda_p_script::cluster::node> (), boost::make_shared <lambda_p::node> (), 1);
	context.nodes [0].push_back (node1);
	context.nodes [0].push_back (node2);
	std::vector <boost::shared_ptr <lambda_p::node>> target;
	reference (errors, context, target);
	assert (errors->errors.empty ());
	assert (target.size () == 1);
	assert (target [0] == node2);
}