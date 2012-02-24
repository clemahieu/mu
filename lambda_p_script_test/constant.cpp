#include "constant.h"

#include <core/node.h>
#include <lambda_p_script/constant.h>
#include <core/errors/error_list.h>
#include <lambda_p_script/context.h>
#include <lambda_p_script/cluster/node.h>

#include <boost/make_shared.hpp>

void lambda_p_script_test::constant::run ()
{
	run_1 ();
}

void lambda_p_script_test::constant::run_1 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	boost::shared_ptr <mu::core::node> node (new mu::core::node);
	lambda_p_script::constant constant (node);
	lambda_p_script::context context (boost::make_shared <lambda_p_script::cluster::node> (), boost::make_shared <mu::core::node> (), 0);
	std::vector <boost::shared_ptr <mu::core::node>> target;
	constant (errors, context, target);
	assert (errors->errors.empty ());
	assert (target.size () == 1);
	assert (target [0] == node);
}