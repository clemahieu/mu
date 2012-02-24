#include "node.h"

#include <mu/core/errors/error_list.h>
#include <mu/script/cluster/node.h>
#include <mu/script/routine.h>
#include <mu/core/routine.h>

#include <boost/make_shared.hpp>

void mu::script_test::cluster::node::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void mu::script_test::cluster::node::run_1 ()
{
	mu::script::cluster::node cluster;
	std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> remap;
	cluster.remap (remap);
}

void mu::script_test::cluster::node::run_2 ()
{
	mu::script::cluster::node cluster;
	auto routine (boost::make_shared <mu::core::routine> (mu::core::context ()));
	std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> remap;
	auto node (boost::make_shared <mu::core::node> ());
	cluster.mapping [routine] = node;
	cluster.remap (remap);
	assert (cluster.routines.size () == 0);
}

void mu::script_test::cluster::node::run_3 ()
{
	mu::script::cluster::node cluster;
	auto routine (boost::make_shared <mu::core::routine> (mu::core::context ()));
	std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> remap;
	auto node (boost::make_shared <mu::core::node> ());
	cluster.mapping [routine] = node;
	cluster.remap (remap);
}

void mu::script_test::cluster::node::run_4 ()
{
	mu::script::cluster::node cluster;
	auto routine (boost::make_shared <mu::core::routine> (mu::core::context ()));
	std::map <boost::shared_ptr <mu::core::node>, boost::shared_ptr <mu::core::node>> remap;
	auto node (boost::make_shared <mu::core::node> ());
	auto node2 (boost::make_shared <mu::core::node> ());
	remap [node] = node2;
	cluster.mapping [routine] = node;
	cluster.remap (remap);
}