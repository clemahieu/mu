#include "get.h"

#include <mu/core/errors/error_list.h>
#include <mu/core/routine.h>
#include <mu/script/cluster/get.h>
#include <mu/script/cluster/node.h>
#include <mu/script/routine.h>
#include <mu/script/cluster/node.h>

#include <boost/make_shared.hpp>

void mu::script_test::cluster::get::run ()
{
	run_1 ();
}

void mu::script_test::cluster::get::run_1 ()
{
	auto routine (boost::make_shared <mu::core::routine> (mu::core::context ()));
	auto script (boost::make_shared <mu::script::routine> (boost::make_shared <mu::script::cluster::node> ()));
	auto cluster (boost::make_shared <mu::script::cluster::node> ());
	cluster->routines.push_back (script);
	cluster->names [std::wstring (L"one")] = routine;
	cluster->mapping [routine] = script;
	auto get (boost::make_shared <mu::script::cluster::get> ());
	auto errors (boost::make_shared <mu::core::errors::error_list> ());
	std::vector <boost::shared_ptr <mu::core::node>> arguments;
	std::vector <boost::shared_ptr <mu::core::node>> results;
	arguments.push_back (cluster);
	arguments.push_back (routine);
	get->perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == script);
}