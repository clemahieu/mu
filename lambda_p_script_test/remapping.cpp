#include "remapping.h"

#include <lambda_p_script/remapping.h>
#include <lambda_p/routine.h>

#include <boost/make_shared.hpp>

void lambda_p_script_test::remapping::run ()
{
	run_1 ();
	run_2 ();
	run_3 ();
	run_4 ();
}

void lambda_p_script_test::remapping::run_1 ()
{
	lambda_p_script::remapping remapping;
	std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> new_l;
	remapping.remap (new_l);
	assert (remapping.generated.size () == 0);
}

void lambda_p_script_test::remapping::run_2 ()
{
	lambda_p_script::remapping remapping;
	std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> new_l;
	new_l [boost::make_shared <lambda_p::node> ()] = boost::make_shared <lambda_p::node> ();
	remapping.remap (new_l);
	assert (remapping.generated.size () == 0);
}

void lambda_p_script_test::remapping::run_3 ()
{
	lambda_p_script::remapping remapping;
	std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> new_l;
	remapping.generated [boost::make_shared <lambda_p::routine> (lambda_p::context ())] = boost::make_shared <lambda_p::node> ();
	remapping.remap (new_l);
	assert (remapping.generated.size () == 0);
}

void lambda_p_script_test::remapping::run_4 ()
{
	lambda_p_script::remapping remapping;
	std::map <boost::shared_ptr <lambda_p::node>, boost::shared_ptr <lambda_p::node>> new_l;
	auto old (boost::make_shared <lambda_p::node> ());
	auto routine (boost::make_shared <lambda_p::routine> (lambda_p::context ()));
	remapping.generated [routine] = old;
	auto val (boost::make_shared <lambda_p::node> ());
	new_l [old] = val;
	assert (remapping.generated.size () == 1);
	assert (remapping.generated [routine] == old);
	remapping.remap (new_l);
	assert (remapping.generated.size () == 1);
	assert (remapping.generated [routine] == val);
}