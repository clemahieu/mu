#include "node.h"

#include <core/errors/error_list.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/routine.h>
#include <core/routine.h>

#include <boost/make_shared.hpp>

void lambda_p_script_test::cluster::node::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_script_test::cluster::node::run_1 ()
{
	lambda_p_script::cluster::node cluster;
	std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> remap;
	cluster.remap (remap);
}

void lambda_p_script_test::cluster::node::run_2 ()
{
	lambda_p_script::cluster::node cluster;
	auto routine (boost::make_shared <mu::core::routine> (mu::core::context ()));
	std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> remap;
	auto node (boost::make_shared <mu::core::node> ());
	cluster.mapping [routine] = node;
	cluster.remap (remap);
	assert (cluster.routines.size () == 0);
}

void lambda_p_script_test::cluster::node::run_3 ()
{
	lambda_p_script::cluster::node cluster;
	auto routine (boost::make_shared <mu::core::routine> (mu::core::context ()));
	std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> remap;
	auto node (boost::make_shared <mu::core::node> ());
	cluster.mapping [routine] = node;
	cluster.remap (remap);
}

void lambda_p_script_test::cluster::node::run_4 ()
{
	lambda_p_script::cluster::node cluster;
	auto routine (boost::make_shared <mu::core::routine> (mu::core::context ()));
	std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> remap;
	auto node (boost::make_shared <mu::core::node> ());
	auto node2 (boost::make_shared <mu::core::node> ());
	remap [node] = node2;
	cluster.mapping [routine] = node;
	cluster.remap (remap);
}