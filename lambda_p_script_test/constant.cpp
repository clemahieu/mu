#include "constant.h"

#include <lambda_p/node.h>
#include <lambda_p_script/constant.h>
#include <lambda_p/errors/error_list.h>
#include <lambda_p_script/context.h>

void lambda_p_script_test::constant::run ()
{
	run_1 ();
}

void lambda_p_script_test::constant::run_1 ()
{
	boost::shared_ptr <lambda_p::errors::error_list> errors (new lambda_p::errors::error_list);
	boost::shared_ptr <lambda_p::node> node (new lambda_p::node);
	lambda_p_script::constant constant (node);
	lambda_p_script::context context (0);
	std::vector <boost::shared_ptr <lambda_p::node>> target;
	constant (errors, context, target);
	assert (errors->errors.empty ());
	assert (target.size () == 1);
	assert (target [0] == node);
}