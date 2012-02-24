#include "call.h"

#include <lambda_p_script/call.h>
#include <lambda_p_script/constant.h>
#include <core/node.h>
#include <core/errors/error_list.h>
#include <lambda_p_script/context.h>
#include <lambda_p_script/identity/operation.h>
#include <lambda_p_script/cluster/node.h>

#include <boost/make_shared.hpp>

void lambda_p_script_test::call::run ()
{
	run_1 ();
}

void lambda_p_script_test::call::run_1 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	boost::shared_ptr <lambda_p_script::call> call (new lambda_p_script::call (1, mu::core::context ()));
	lambda_p_script::context context (boost::make_shared <lambda_p_script::cluster::node> (), boost::make_shared <mu::core::node> (), 2);
	call->arguments.push_back (boost::shared_ptr <lambda_p_script::constant> (new lambda_p_script::constant (boost::shared_ptr <mu::core::node> (new lambda_p_script::identity::operation))));
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	call->arguments.push_back (boost::shared_ptr <lambda_p_script::constant> (new lambda_p_script::constant (node)));
	(*call) (errors, context);
	assert (context.nodes [1].size () == 1);
	assert (context.nodes [1] [0] == node);
}