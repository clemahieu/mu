#include "expression.h"

#include <mu/script/expression.h>
#include <mu/core/node.h>
#include <mu/core/errors/error_list.h>
#include <mu/script/context.h>
#include <mu/script/cluster/node.h>

#include <boost/make_shared.hpp>

void lambda_p_script_test::expression::run ()
{
	run_1 ();
	run_2 ();
}

void lambda_p_script_test::expression::run_1 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	boost::shared_ptr <mu::core::node> node (new mu::core::node);
	mu::script::expression expression (0);
	mu::script::context context (boost::make_shared <mu::script::cluster::node> (), boost::make_shared <mu::core::node> (), 1);
	context.nodes [0].push_back (node);
	std::vector <boost::shared_ptr <mu::core::node>> target;
	expression (errors, context, target);
	assert (errors->errors.empty ());
	assert (target.size () == 1);
	assert (target [0] == node);
}

void lambda_p_script_test::expression::run_2 ()
{
	boost::shared_ptr <mu::core::errors::error_list> errors (new mu::core::errors::error_list);
	boost::shared_ptr <mu::core::node> node1 (new mu::core::node);
	boost::shared_ptr <mu::core::node> node2 (new mu::core::node);
	mu::script::expression expression (0);
	mu::script::context context (boost::make_shared <mu::script::cluster::node> (), boost::make_shared <mu::core::node> (), 1);
	context.nodes [0].push_back (node1);
	context.nodes [0].push_back (node2);
	std::vector <boost::shared_ptr <mu::core::node>> target;
	expression (errors, context, target);
	assert (errors->errors.empty ());
	assert (target.size () == 2);
	assert (target [0] == node1);
	assert (target [1] == node2);
}