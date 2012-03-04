#include "call.h"

#include <mu/script/runtime.call.h>
#include <mu/script/runtime.constant.h>
#include <mu/core/node.h>
#include <mu/core/errors.error_list.h>
#include <mu/script/runtime.context.h>
#include <mu/script/identity.operation.h>
#include <mu/script/cluster.node.h>

#include <boost/make_shared.hpp>

void mu::script_test::call::run ()
{
	run_1 ();
}

void mu::script_test::call::run_1 ()
{
	auto errors (boost::shared_ptr <mu::core::errors::error_list> (new mu::core::errors::error_list));
	boost::shared_ptr <mu::script::runtime::call> call (new mu::script::runtime::call (1, mu::core::context ()));
	mu::script::runtime::context context (boost::make_shared <mu::script::cluster::node> (), boost::make_shared <mu::core::node> (), 2);
	call->arguments.push_back (boost::shared_ptr <mu::script::runtime::constant> (new mu::script::runtime::constant (boost::shared_ptr <mu::core::node> (new mu::script::identity::operation))));
	auto node (boost::shared_ptr <mu::core::node> (new mu::core::node));
	call->arguments.push_back (boost::shared_ptr <mu::script::runtime::constant> (new mu::script::runtime::constant (node)));
	(*call) (errors, context);
	assert (context.nodes [1].size () == 1);
	assert (context.nodes [1] [0] == node);
}