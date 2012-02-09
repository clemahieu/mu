#include "get.h"

#include <lambda_p/errors/error_list.h>
#include <lambda_p/routine.h>
#include <lambda_p_script/cluster/get.h>
#include <lambda_p_script/cluster/node.h>
#include <lambda_p_script/routine.h>
#include <lambda_p_script/remapping.h>

#include <boost/make_shared.hpp>

void lambda_p_script_test::cluster::get::run ()
{
	run_1 ();
}

void lambda_p_script_test::cluster::get::run_1 ()
{
	auto routine (boost::make_shared <lambda_p::routine> (lambda_p::context ()));
	auto script (boost::make_shared <lambda_p_script::routine> ());
	auto cluster (boost::make_shared <lambda_p_script::cluster::node> ());
	cluster->routines.push_back (script);
	cluster->names [std::wstring (L"one")] = 0;
	cluster->remapping->generated [routine] = script;
	auto get (boost::make_shared <lambda_p_script::cluster::get> ());
	auto errors (boost::make_shared <lambda_p::errors::error_list> ());
	std::vector <boost::shared_ptr <lambda_p::node>> arguments;
	std::vector <boost::shared_ptr <lambda_p::node>> results;
	arguments.push_back (cluster);
	arguments.push_back (routine);
	get->perform (errors, arguments, results);
	assert (errors->errors.empty ());
	assert (results.size () == 1);
	assert (results [0] == script);
}