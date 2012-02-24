#include "constant.h"

#include <mu/core/node.h>
#include <mu/script/constant.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/cluster/node.h>

#include <boost/make_shared.hpp>

void lambda_p_script_test::constant::run ()
{
	run_1 ();
}

void lambda_p_script_test::constant::run_1 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	boost::shared_ptr <mu::core::node> node (new mu::core::node);
	mu::script::constant constant (node);
	mu::script::context context (boost::make_shared <mu::script::cluster::node> (), boost::make_shared <mu::core::node> (), 0);
	std::vector <boost::shared_ptr <mu::core::node>> target;
	constant (errors, context, target);
	assert (errors->errors.empty ());
	assert (target.size () == 1);
	assert (target [0] == node);
}